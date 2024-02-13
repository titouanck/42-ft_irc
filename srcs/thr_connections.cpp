/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_connections.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 18:16:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thr_connections.hpp"
#include "thr_timeout.hpp"
#include "Server.hpp"

#define BUFFER_SIZE 4096

/* ************************************************************************** */

void	handleMessage(Client &client, Message message)
{
	if (message.command.length() == 0);
	else if (message.command.compare("CAP") == 0)
		client.CAP(message.content);
	else if (message.command.compare("PASS") == 0)
		client.PASS(message.content);
	else if (message.command.compare("NICK") == 0)
		client.NICK(message.content);
	else if (message.command.compare("USER") == 0)
		client.USER(message.content);
	else if (message.command.compare("PONG") == 0)
		client.PONG(message.content);
	else if (message.command.compare("JOIN") == 0)
		client.JOIN(message.content);
	else if (message.command.compare("LEAVE") == 0)
		client.LEAVE(message.content);
}

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
	// RECURSIVITY WITH EACH LINE OF THE CLIENT INPUT
	size_t	pos;
	Message	message;

	if (endsWith(input, "\r\n"))
		input = input.substr(0, input.length() - 2);
	if (input.length() <= 0)
		return ;
	pos = input.find("\r\n");
	if (pos != string_t::npos)
	{
		handleClientInput(client, input.substr(0, pos));
		handleClientInput(client, input.substr(pos + 2));
		return ;
	}
	handleMessage(client, parseInput(input));
}

void	readSocket(Client &client)
{
	ssize_t bytesRead;
	char 	buffer[BUFFER_SIZE];
	int		index;

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
	std::cout << " username: " << client.getUsername() << '\n';
	std::cout << " realname: " << client.getRealname() << '\n';
	std::cout << "----------------------------------------" << '\n';
	handleClientInput(client, buffer);
}

void	*thr_connections(void *arg)
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
					handleConn(clients);
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
