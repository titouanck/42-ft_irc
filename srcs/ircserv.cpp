/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 15:15:58 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ircserv.hpp"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

#define BUFFER_SIZE 4096

typedef struct s_data
{
	Server	&server;
	Pollfd	(&pollfds)[MAX_CLIENTS + 1];
	Client	(&clients)[MAX_CLIENTS + 1];
}	Data;

typedef struct s_message
{
	std::string	command;
	std::string	content;
}	Message;

/* ************************************************************************** */

void	*timeoutThread(void *arg)
{
	Data	*data = reinterpret_cast<Data *>(arg);
	Pollfd	(&pollfds)[MAX_CLIENTS + 1] = data->pollfds;
	Client	(&clients)[MAX_CLIENTS + 1] = data->clients;

	while (true)
	{
		for (int i = 0; i <= MAX_CLIENTS; i++)
		{
			clients[i].lockMutex();
			if (clients[i].getIdentity().length() != 0)
			{
				if (clients[i].isPinged() == true && clients[i].getPingTime() + TIMEOUTSEC < std::time(0))
					removeConn(pollfds[i], clients[i], i);
			}
			clients[i].unlockMutex();
		}
	}
	pthread_exit(NULL);
}

bool endsWith(const std::string &str, const std::string &suffix)
{
    if (str.length() < suffix.length())
        return false;
    else
	    return str.substr(str.length() - suffix.length()) == suffix;
}

Message	parseMessage(std::string line)
{
	Message		message;
	size_t		pos;
	
	bzero(&message, sizeof(message));
	pos = line.find_first_of(" \t");
	if (pos != std::string::npos)
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

void	handleClientMessage(Pollfd (&pollfds)[MAX_CLIENTS + 1], Client &client, int i, std::string rawMessage)
{
	size_t	pos;
	Message	message;

	if (endsWith(rawMessage, "\r\n"))
		rawMessage = rawMessage.substr(0, rawMessage.length() - 2);
	if (rawMessage.length() <= 0)
		return ;
	pos = rawMessage.find("\r\n");
	if (pos != std::string::npos)
	{
		handleClientMessage(pollfds, client, i, rawMessage.substr(0, pos));
		handleClientMessage(pollfds, client, i, rawMessage.substr(pos + 2));
		return ;
	}

	message = parseMessage(rawMessage);
	if (message.command.compare("PASS") == 0)
	{
		if (client.isAuthenticated())
			return (removeConn(pollfds[i], client, i));
		client.beAuthenticated(message.content);
	}
}

void	readSocket(Pollfd (&pollfds)[MAX_CLIENTS + 1], Client &client, int i)
{
	ssize_t bytesRead;
	char 	buffer[BUFFER_SIZE];

	bytesRead = read(pollfds[i].fd, buffer, sizeof(buffer));
	if (bytesRead <= 0)
		return (removeConn(pollfds[i], client, i));
	buffer[bytesRead] = '\0';
	handleClientMessage(pollfds, client, i, buffer);
}

bool routine(Server &server, Pollfd (&pollfds)[MAX_CLIENTS + 1], Client (&clients)[MAX_CLIENTS + 1])
{
	Data		data = {server, pollfds, clients};
	int			result;
	int			threadResult;
	pthread_t	thread;
	char 		buffer[BUFFER_SIZE];(void)buffer;

	threadResult = pthread_create(&thread, NULL, timeoutThread, &data);
	if (threadResult != 0)
    	return printError("pthread_create"), false;
	while (true)
	{
		result = poll(pollfds, MAX_CLIENTS + 2, 250);
        if (result == -1)
			return printError("poll"), pthread_join(thread, NULL), false;
		for (int i = 0; i <= MAX_CLIENTS; ++i)
		{
			clients[i].lockMutex();
            if (pollfds[i].revents == POLLIN)
			{
				if (i == 0)
					handleConn(server, pollfds, clients);
				else
					readSocket(pollfds, clients[i], i);
			}
			clients[i].unlockMutex();
		}
	}
	threadResult = pthread_join(thread, NULL);
}

bool	ircserv(unsigned int port, std::string password)
{
	Server	server(port, password);
	Pollfd	pollfds[MAX_CLIENTS + 1];
	Client	clients[MAX_CLIENTS + 1];
	bool	status;

	Client::server  = &server;
	Client::pollfds = pollfds;
	if (!server.init())
		return false;
    bzero(pollfds, sizeof(pollfds));
    bzero(clients, sizeof(clients));

	pollfds[0].fd = server.getSocket();
    pollfds[0].events = POLLIN;
	status = routine(server, pollfds, clients);
	server.closeSocket();
	return status;
}

/* ************************************************************************** */
