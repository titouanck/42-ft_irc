/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:53:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 17:18:20 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connections.hpp"

/* ************************************************************************** */

static void	printConn(connStatus status, const Client &client, int nbr)
{
	switch (status)
	{
		case '+':
			std::cout << GREEN	<< "[+] client " << nbr << " (" << client.getIdentity() << ")" NC << '\n';
			break ;
		case '-':
			std::cout << RED	<< "[-] client " << nbr << " (" << client.getIdentity() << ")" NC << '\n';
			break ;
		case '!':
			std::cout << ORANGE	<< "[!] Cannot connect with " << client.getIdentity() << ", too many clients (see MAX_CLIENTS)" NC << '\n';
			break ;
	}
}

/* ************************************************************************** */

void	removeConn(Pollfd &pollfd, Client &client, int nbr)
{
	close(pollfd.fd);
	bzero(&pollfd, sizeof(pollfd));
	printConn('-', client, nbr);
	bzero(&client, sizeof(client));
}

/* ************************************************************************** */

static void	rejectConn(Server &server)
{
	Client	client;
	SOCKET	clientFd;

	client.len = sizeof(client.addr);
	clientFd = accept(server.getSocket(), reinterpret_cast<Sockaddr *>(&client.addr), &client.len);
	if (clientFd == -1)
		return printError("accept"), static_cast<void>(0);
	client.setIdentity();
	printConn('!', client, MAX_CLIENTS + 1);
	close(clientFd);
}

static void	acceptConn(Server &server, Pollfd &pollfd, Client &client, int i)
{
	bzero(&(client), sizeof(client));
	client.len = sizeof(client.addr);
	pollfd.fd = accept(server.getSocket(), (Sockaddr *)&(client.addr), &(client.len));
	if (pollfd.fd == -1)
	{
		pollfd.events = 0;
		printError("accept");
		return ;
	}
	pollfd.events = POLLIN;
	client.setIdentity();
	printConn('+', client, i);
}

void	handleConn(Server &server, Pollfd (&pollfds)[MAX_CLIENTS + 1], Client (&clients)[MAX_CLIENTS + 1])
{
	int i;

	for (i = 1; i < MAX_CLIENTS + 1; ++i)
	{
		if (pollfds[i].fd == 0)
			return acceptConn(server, pollfds[i], clients[i], i), static_cast<void>(0);
	}
	if (i == MAX_CLIENTS + 1)
		rejectConn(server);
}

/* ************************************************************************** */
