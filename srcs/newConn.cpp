/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newConn.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:53:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/14 01:44:17 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "newConn.hpp"
#include "numericReferences.hpp"

/* ************************************************************************** */

void	printConn(unsigned char connStatus, const Client &client)
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
			std::cout << ORANGE	<< "[!] Cannot connect with " << client.getIdentity() << ", too many clients. " RED "[> " << MAX_CLIENTS << "]" NC << '\n';
			break ;
		default:
			return ;
	}
	std::cout << "----------------------------------------" << '\n';
}

/* ************************************************************************** */

static void	rejectConn()
{
	Client		client;
	socket_t	clientFd;

	client.len = sizeof(client.addr);
	clientFd = accept(Server::sock, reinterpret_cast<sockaddr_t *>(&client.addr), &client.len);
	if (clientFd == -1)
		return printError("accept");
	client.setIdentity();
	printConn('!', client);
	close(clientFd);
}

static void	acceptConn(Client &client, int index)
{
	pollfd_t	&pollfd = g_pollfds[index];

	client.len = sizeof(client.addr);
	pollfd.fd = accept(Server::sock, (sockaddr_t *)&(client.addr), &(client.len));
	if (pollfd.fd == -1)
		return printError("accept");
	pollfd.events = POLLIN;
	client.setIndex(index);
	client.setIdentity();
	printConn('+', client);
}

void	handleConn(Client *clients)
{
	pollfd_t	*pollfds = g_pollfds;
	int 		index;

	for (index = 1; index < MAX_CLIENTS + 1; ++index)
	{
		if (pollfds[index].fd == 0)
			return acceptConn(clients[index], index);
	}
	if (index == MAX_CLIENTS + 1)
		rejectConn();
}

/* ************************************************************************** */
