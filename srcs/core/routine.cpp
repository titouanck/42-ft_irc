/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:15:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/27 19:04:08 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/routine.hpp"
#include "commands/callCorrespondingCommand.hpp"
#include "classes/Server.hpp"
#include "classes/Client.hpp"

#define BUFFER_SIZE 2

/* ************************************************************************** */

Message	parseInput(string_t line)
{
	Message		message;
	size_t		pos;
	
	while (line.length() > 0 && (line[0] == ' ' || line[0] == '\t'))
		line = line.substr(1);
	if (line.empty())
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

	if (input.empty())
		return ;
	pos = 0;
    while (true)
	{
		pos = input.find('\r', pos);
		if (pos == std::string::npos)
			break ;
		input.erase(pos, 1);
	}
	if (input.compare("\n") == 0)
	{
		callCorrespondingCommand(client, parseInput(client.getBuffer()));
		if (client.getIp().empty() == false)
			client.clearBuffer();
		return ;
	}
	pos = input.find('\n');
	if (pos != string_t::npos)
		remaining = input.substr(pos + 1);
	toAdd = input.substr(0, pos);
	client.appendToBuffer(toAdd);
	if (pos != string_t::npos)
	{
		callCorrespondingCommand(client, parseInput(client.getBuffer()));
		if (client.getIp().empty())
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

	// if (client.getNickname().empty())
	// 	std::cout << "(" << RED << "CLIENT " << client.getIndex() << NC ") " << MAGENTA << buffer << NC;
	// else
	// 	std::cout << "(" << RED << client.getNickname() << NC ") " << MAGENTA << buffer << NC;
	// if (!endsWith(buffer, "\n"))
	// 	std::cout << '\n';
	// clientInfo = client.getUsername();
	// if (clientInfo.length() > 0)
	// 	std::cout << " username: " << clientInfo << '\n';
	// clientInfo = client.getRealname();
	// if (clientInfo.length() > 0)
	// 	std::cout << " realname: " << clientInfo << '\n';
	// clientInfo = client.getIdentity();
	// if (clientInfo.compare(client.getName()) == 0)
	// 	std::cout << " host: " << clientInfo << " [" << client.getIp() << "]" << '\n';
	// else
	// 	std::cout << " host: " << clientInfo << '\n';
	handleClientInput(client, buffer);
	// if (client.getIp().length() != 0)
	// 	std::cout << "----------------------------------------" << '\n';
}

void	routine()
{
	int	pollResult;

	while (true)
	{
		pollResult = poll(g_pollfds, MAX_CLIENTS + 1, -1);
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
