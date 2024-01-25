/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:53:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 17:03:26 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connections.hpp"

/* ************************************************************************** */

static void	printConn(unsigned char connStatus, const Client &client)
{
	switch (connStatus)
	{
		case '+':
			std::cout << GREEN	<< "[+] client " << client.getIndex() << " (" << client.getIdentity() << ")" NC << '\n';
			break ;
		case '-':
			std::cout << RED	<< "[-] client " << client.getIndex() << " (" << client.getIdentity() << ")" NC << '\n';
			break ;
		case '!':
			std::cout << ORANGE	<< "[!] Cannot connect with " << client.getIdentity() << ", too many clients (see MAX_CLIENTS)" NC << '\n';
			break ;
	}
}

/* ************************************************************************** */

void	removeConn(Client &client)
{
	pollfd_t	&pollfd = Client::pollfds[client.getIndex()];

	close(pollfd.fd);
	bzero(&pollfd, sizeof(pollfd));
	printConn('-', client);
	bzero(&client, sizeof(client));
}

/* ************************************************************************** */

static void	rejectConn(Server *server)
{
	Client		client;
	socket_t	clientFd;

	client.len = sizeof(client.addr);
	clientFd = accept(server->sock, reinterpret_cast<sockaddr_t *>(&client.addr), &client.len);
	if (clientFd == -1)
		return printError("accept");
	client.setIdentity();
	printConn('!', client);
	close(clientFd);
}

static void	acceptConn(Client &client, int index)
{
	Server		*server = Client::server;
	pollfd_t	&pollfd = Client::pollfds[index];

	client.len = sizeof(client.addr);
	pollfd.fd = accept(server->sock, (sockaddr_t *)&(client.addr), &(client.len));
	if (pollfd.fd == -1)
		return printError("accept");
	pollfd.events = POLLIN;
	client.setIndex(index);
	client.setIdentity();
	printConn('+', client);
}

void	handleConn(Client *clients)
{
	Server		*server  = Client::server;
	pollfd_t	*pollfds = Client::pollfds;
	int 		index;

	for (index = 1; index < MAX_CLIENTS + 1; ++index)
	{
		if (pollfds[index].fd == 0)
			return acceptConn(clients[index], index);
	}
	if (index == MAX_CLIENTS + 1)
		rejectConn(server);
}

/* ************************************************************************** */
