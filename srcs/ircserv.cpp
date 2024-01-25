/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 17:52:31 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ircserv.hpp"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

#define BUFFER_SIZE 4096

/* ************************************************************************** */

void	*timeoutThread(void *arg)
{
	Client	*clients = (static_cast<Client (*)>(arg));

	while (true)
	{
		for (int i = 0; i <= MAX_CLIENTS; i++)
		{
			clients[i].lockMutex();
			if (clients[i].getIdentity().length() != 0)
			{
				if (clients[i].isPinged() == true && clients[i].getPingTime() + TIMEOUTSEC < std::time(0))
					removeConn(clients[i]);
			}
			clients[i].unlockMutex();
		}
	}
	pthread_exit(NULL);
}

bool endsWith(const string_t &str, const string_t &suffix)
{
    if (str.length() < suffix.length())
        return false;
    else
	    return str.substr(str.length() - suffix.length()) == suffix;
}

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

bool routine(pollfd_t *pollfds, Client *clients)
{
	int			pollResult;
	pthread_t	thread;

	if (pthread_create(&thread, NULL, timeoutThread, &clients) != 0)
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

bool	ircserv(unsigned int port, string_t password)
{
	Server		server(port, password);
	pollfd_t	pollfds[MAX_CLIENTS + 1];
	Client		clients[MAX_CLIENTS + 1];
	bool		status;
	
	if (!server.init())
		return false;
    bzero(pollfds, sizeof(pollfds));
    bzero(clients, sizeof(clients));
	pollfds[0].fd = server.sock;
    pollfds[0].events = POLLIN;

	Client::server  = &server;
	Client::pollfds = pollfds;
	status = routine(pollfds, clients);
	
	server.closeSocket();
	return status;
}

/* ************************************************************************** */
