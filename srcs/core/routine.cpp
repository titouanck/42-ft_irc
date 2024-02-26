/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:15:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 17:07:42 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/routine.hpp"
#include "commands/callCorrespondingCommand.hpp"
#include "classes/Server.hpp"
#include "classes/Client.hpp"

#define BUFFER_SIZE 4096

/* ************************************************************************** */

Message	parseInput(string_t line)
{
	Message		message;
	size_t		pos;
	
	if (line.length() == 0)
		return ((Message){"", ""});
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
	string_t	remaining;
	string_t	toAdd;
	size_t		pos;

	if (input.length() <= 0)
		return ;
	pos = input.find('\n');
	if (pos != string_t::npos)
	{
		remaining = input.substr(pos + 1);
		if (pos > 0 && input[pos - 1] == '\r')
			pos -= 1;
	}
	toAdd = input.substr(0, pos);
	client.appendToBuffer(toAdd);
	if (pos != string_t::npos)
	{
		callCorrespondingCommand(client, parseInput(client.getBuffer()));
		if (client.getIp().length() == 0)
			return ;
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
	if (client.getIp().length() != 0)
		std::cout << "----------------------------------------" << '\n';
}

void	routine()
{
	int	pollResult;

	while (true)
	{
		pollResult = poll(g_pollfds, MAX_CLIENTS + 1, 250);
        if (pollResult == -1)
		{
			printError("poll");
			break ;
		}
		for (int i = 0; i <= MAX_CLIENTS; ++i)
		{
            if (g_pollfds[i].revents == POLLIN)
			{
				if (i == 0)
					handleNewConnection(g_clients);
				else
					readSocket(g_clients[i]);
			}
		}
	}
}

/* ************************************************************************** */
