/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 11:46:44 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ircserv.hpp"
#include <stdio.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

/* ************************************************************************** */

void	rejectConnection(Server &server, Pollfd &pollfd)
{
	SOCKET			clientFd;
	Sockaddr_in6	clientAddr;
	socklen_t		clientLen;

	clientLen = sizeof(clientAddr);
	clientFd = accept(server.getSocket(), (Sockaddr *)&clientAddr, &clientLen);
	if (clientFd == -1)
		return printError("accept"), static_cast<void>(0);
	close(clientFd);
	pollfd.fd = clientFd;
	pollfd.events = POLLIN;
}

void	handleConnection(Server &server, Pollfd (&pollfds)[MAX_CLIENTS + 1], Client (&clients)[MAX_CLIENTS])
{
	int i;

	for (i = 0; i < MAX_CLIENTS; ++i)
	{
		if (clients[i].fd == 0)
		{
			clients[i].len = sizeof(clients[i].addr);
			clients[i].fd = accept(server.getSocket(), (Sockaddr *)&(clients[i].addr), &(clients[i].len));
			if (clients[i].fd == -1)
				return printError("accept"), static_cast<void>(0);
			pollfds[i + 1].fd = clients[i].fd;
			pollfds[i + 1].events = POLLIN;
			std::cout << "New client connection from " << getHostInfo(clients[i].addr) << " on socket " << clients[i].fd << '\n';
			break;
		}
	}
	if (i == MAX_CLIENTS)
		rejectConnection(server, pollfds[i + 1]);
}

void	readSocket(Pollfd (&pollfds)[MAX_CLIENTS + 1], Client &client, int i)
{
	ssize_t bytesRead;
	char 	buffer[BUFFER_SIZE];

	bytesRead = read(pollfds[i].fd, buffer, sizeof(buffer));
	if (bytesRead <= 0)
	{
		std::cout << "Client disconnected from socket " << pollfds[i].fd << '\n';
		close(pollfds[i].fd);
		pollfds[i].fd = 0;
		pollfds[i].fd = 0;
		return ;
	}
	buffer[bytesRead] = '\0';
	std::cout << "Message from " << getHostInfo(client.addr) << " " << pollfds[i].fd << " : " << buffer;
	for (int j = 1; j <= MAX_CLIENTS; ++j)
	{
		if (pollfds[j].fd != pollfds[i].fd && pollfds[j].fd != 0)
			write(pollfds[j].fd, buffer, static_cast<std::string>(buffer).length());
	}
}

bool routine(Server &server, Pollfd (&pollfds)[MAX_CLIENTS + 1], Client (&clients)[MAX_CLIENTS])
{
	int		result;

	while (true)
	{
		result = poll(pollfds, MAX_CLIENTS + 1, -1);
        if (result == -1)
			return printError("poll"), false;
		else if (pollfds[0].revents == POLLIN)
			handleConnection(server, pollfds, clients);
		for (int i = 1; i <= MAX_CLIENTS; ++i)
		{
            if (pollfds[i].revents != POLLIN)
				continue ;
			readSocket(pollfds, clients[i - 1], i);
		}
	}
}

bool	ircserv(unsigned int port, std::string password)
{
	Server	server(port, password);
	Pollfd	pollfds[MAX_CLIENTS + 1];
	Client	clients[MAX_CLIENTS];
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
