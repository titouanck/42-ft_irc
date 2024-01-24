/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 21:42:48 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ircserv.hpp"
#include <pthread.h>
#include <stdio.h>

#define BUFFER_SIZE 4096

/* ************************************************************************** */

void	*timeoutThread(void *arg)
{
	Client	*clients = reinterpret_cast<Client *>(arg);
	while (true)
	{
		for (int i = 0; i <= MAX_CLIENTS; i++)
		{
			if (clients[i].getIdentity().length() != 0)
			{
				if (clients[i].isPinged() == true && clients[i].getPingTime() + TIMEOUTSEC < std::time(0))
					std::cout << "Client " << i << " (" << clients[i].getIdentity() << ") TIMEOUT" << '\n';
			}
		}
	}
	pthread_exit(NULL);
}

void	handleClientMessage(Pollfd (&pollfds)[MAX_CLIENTS + 1], Client &client, int i, std::string message)
{
	std::cout << "Message from " << client.getIdentity() << " = " << message;
	for (int j = 1; j <= MAX_CLIENTS; ++j)
	{
		if (pollfds[j].fd != pollfds[i].fd && pollfds[j].fd != 0)
			write(pollfds[j].fd, message.c_str(), message.length());
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
	int			result;
	int			threadResult;
	pthread_t	thread;

	threadResult = pthread_create(&thread, NULL, timeoutThread, clients);
	if (threadResult != 0)
    	return std::cerr << "Error creating thread: " << threadResult << std::endl, false;
	while (true)
	{
		result = poll(pollfds, MAX_CLIENTS + 1, -1);
        if (result == -1)
			return printError("poll"), false;
		else if (pollfds[0].revents == POLLIN)
			handleConn(server, pollfds, clients);
		for (int i = 1; i <= MAX_CLIENTS; ++i)
		{
            if (pollfds[i].revents != POLLIN)
				continue ;
			readSocket(pollfds, clients[i], i);
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

	if (!server.init())
		return false;
    bzero(pollfds, sizeof(pollfds));
    bzero(clients, sizeof(clients));
	pollfds[0].fd = server.getSocket();
    pollfds[0].events = POLLIN;

	status = routine(server, pollfds, clients);
	close(server.getSocket());
	return status;
}

/* ************************************************************************** */
