/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:15:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 19:27:04 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/routine.hpp"
#include "connections/timeout.hpp"
#include "commands/callCorrespondingCommand.hpp"
#include "classes/Server.hpp"
#include "classes/Client.hpp"

#define BUFFER_SIZE 4096

/* ************************************************************************** */

Message	parseInput(string_t line)
{
	Message		message;
	size_t		pos;
	
	bzero(&message, sizeof(message));
	pos = line.find_first_of(" \t");
	if (pos != string_t::npos)
	{
		message.command = line.substr(0, pos);
		message.content = line.substr(pos);
		while (message.content[0] == ' ' || message.content[0] == '\t')
			message.content = message.content.substr(1);
	}
	else
		message.command = line;
	return message;
}

void	handleClientInput(Client &client, string_t input)
{
	(void)	client;
	(void)	input;
	size_t		pos;
	string_t	remaining;

	std::cout << "ICI COUCOU" << '\n';
	
	if (input.length() <= 0)
		return ;
	pos = input.find('\n');
	if (pos != string_t::npos)
	{
		remaining = input.substr(pos);
		if (pos > 0 && input[pos - 1] == '\r')
			pos -= 1;
	}
	client.appendToBuffer(input.substr(0, pos));
	if (pos != string_t::npos)
	{
		callCorrespondingCommand(client, parseInput(client.getBuffer()));
		client.clearBuffer();
	}
	handleClientInput(client, remaining);
}

void	readSocket(Client &client)
{
	ssize_t 	bytesRead;
	char 		buffer[BUFFER_SIZE];
	int			index;
	string_t	clientInfo;

	index = client.getIndex();
	bytesRead = read(g_pollfds[index].fd, buffer, sizeof(buffer));
	if (bytesRead <= 0)
		return (client.disconnect());
	buffer[bytesRead] = '\0';

	if (client.getNickname().length() == 0)
		std::cout << "(" << RED << "CLIENT " << client.getIndex() << NC ") " << MAGENTA << buffer << NC;
	else
		std::cout << "(" << RED << client.getNickname() << NC ") " << MAGENTA << buffer << NC;
	if (!endsWith(buffer, "\n"))
		std::cout << '\n';
	clientInfo = client.getUsername();
	if (clientInfo.length() > 0)
		std::cout << " username: " << clientInfo << '\n';
	clientInfo = client.getRealname();
	if (clientInfo.length() > 0)
		std::cout << " realname: " << clientInfo << '\n';
	clientInfo = client.getIdentity();
	if (clientInfo.compare(client.getName()) == 0)
		std::cout << " host: " << clientInfo << " [" << client.getIp() << "]" << '\n';
	else
		std::cout << " host: " << clientInfo << '\n';
	handleClientInput(client, buffer);
	std::cout << "----------------------------------------" << '\n';
}

void	*routine(void *arg)
{
	Client		*clients = (static_cast<Client (*)>(arg));
	pollfd_t	*pollfds = g_pollfds;
	int			pollResult;

	while (true)
	{
		pollResult = poll(pollfds, MAX_CLIENTS + 1, 250);
        if (pollResult == -1)
		{
			printError("poll");
			break ;
		}
		for (int i = 0; i <= MAX_CLIENTS; ++i)
		{
			clients[i].lockMutex();
            if (pollfds[i].revents == POLLIN)
			{
				if (i == 0)
					handleNewConnection(clients);
				else
					readSocket(clients[i]);
			}
			clients[i].unlockMutex();
		}
	}
	pthread_mutex_lock(&g_endOfProgram_mutex);
	g_endOfProgram = true;
	pthread_mutex_unlock(&g_endOfProgram_mutex);
	pthread_exit(NULL);
}

/* ************************************************************************** */
