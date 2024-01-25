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

Message	parseMessage(string_t line)
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

void	handleClientMessage(Client &client, string_t rawMessage)
{
	size_t	pos;
	Message	message;

	if (endsWith(rawMessage, "\r\n"))
		rawMessage = rawMessage.substr(0, rawMessage.length() - 2);
	if (rawMessage.length() <= 0)
		return ;
	pos = rawMessage.find("\r\n");
	if (pos != string_t::npos)
	{
		handleClientMessage(client, rawMessage.substr(0, pos));
		handleClientMessage(client, rawMessage.substr(pos + 2));
		return ;
	}
	message = parseMessage(rawMessage);
	if (message.command.compare("PASS") == 0)
		client.beAuthenticated(message.content);
}

void	readSocket(Client &client)
{
	ssize_t bytesRead;
	char 	buffer[BUFFER_SIZE];
	int		index;

	index = client.getIndex();
	bytesRead = read(Client::pollfds[index].fd, buffer, sizeof(buffer));
	if (bytesRead <= 0)
		return (removeConn(client));
	buffer[bytesRead] = '\0';
	handleClientMessage(client, buffer);
}

bool thr_connections(pollfd_t *pollfds, Client *clients)
{
	int			pollResult;
	pthread_t	thread;

	if (pthread_create(&thread, NULL, thr_timeout, &clients) != 0)
    	return printError("pthread_create"), false;
	while (true)
	{
		pollResult = poll(pollfds, MAX_CLIENTS + 1, 250);
        if (pollResult == -1)
			return printError("poll"), pthread_join(thread, NULL), false;
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
	pthread_join(thread, NULL);
}

/* ************************************************************************** */
