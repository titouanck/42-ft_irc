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
	message = parseInput(input);

	// HANDLE MESSAGE
	if (message.command.compare("PASS") == 0)
		client.beAuthenticated(message.content);
}

void	readSocket(Client &client)
{
	ssize_t bytesRead;
	char 	buffer[BUFFER_SIZE];
	int		index;

	index = client.getIndex();
	bytesRead = read(IRC::pollfds[index].fd, buffer, sizeof(buffer));
	if (bytesRead <= 0)
		return (removeConn(client));
	buffer[bytesRead] = '\0';
	handleClientInput(client, buffer);
}

void	*thr_connections(void *arg)
{
	int			rval = true;
	int			pollResult;
	pthread_t	thread_timeout;

	if (pthread_create(&thread_timeout, NULL, thr_timeout, &clients) != 0)
    	return printError("pthread_create(&thread_timeout, ...)"), false;
	while (true)
	{
		pollResult = poll(pollfds, MAX_CLIENTS + 1, 250);
        if (pollResult == -1)
		{
			printError("poll");
			rval = false;
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
	pthread_mutex_lock(&EOP_mutex);
	EOP = true;
	pthread_mutex_unlock(&EOP_mutex);
	pthread_join(thread_timeout, NULL);
	return rval;
}

/* ************************************************************************** */