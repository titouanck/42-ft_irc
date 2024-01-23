/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/23 15:15:21 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include "ircserv.hpp"
#include <stdio.h>
#include "get_next_line.h"

/* ************************************************************************** */

bool	ircserv(unsigned int port, std::string password)
{
	Socket		sock(port, password);
	int			clientSocket;
	socklen_t	addrlen;

	if (!sock.init())
		return false;
	while (true)
	{
		clientSocket = accept(sock._sockfd, (SOCKADDR *)&sock._sin6, &addrlen);
	
		/* ********************************************************************** */
	
		char		host[NI_MAXHOST];
		char		serv[NI_MAXSERV];
		
		bzero(host, NI_MAXHOST);
		bzero(serv, NI_MAXSERV);
		if (getnameinfo((SOCKADDR *)&sock._sin6, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, 0) == 0)
			std::cout << host << " connected on port " << serv << '\n';
		else
		{
			inet_ntop(AF_INET6, &sock._sin6.sin6_addr, host, NI_MAXHOST);
			std::cout << host << " connected on the port " << ntohs(sock._sin6.sin6_port) << '\n';
		}
		
		/* ********************************************************************** */
		
		char	buffer[4096];
		ssize_t	bytesReceived;

		while (true)
		{
			bzero(buffer, 4096);
			bytesReceived = recv(clientSocket, buffer, 4096, 0);
			if (bytesReceived == -1)
			{
				std::cerr << "Error in bytesReceived: " << std::strerror(errno) << '\n';
				break ;
			}
			else if (bytesReceived == 0)
			{
				std::cout << "Client disconnected" << '\n';
				break ;
			}
			std::cout << buffer;
			send(clientSocket, buffer, bytesReceived + 1, 0);
		}
		close(clientSocket);
	}
	return true;
}

/* ************************************************************************** */
