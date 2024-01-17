/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 21:41:20 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include "ircserv.hpp"
#include <stdio.h>
#include "get_next_line.h"

/* ************************************************************************** */

SOCKADDR_IN		addr_ipv4(unsigned int port)
{
	SOCKADDR_IN		sin_ipv4;
	
	sin_ipv4.sin_family = AF_INET;
	sin_ipv4.sin_addr.s_addr = INADDR_ANY;
	sin_ipv4.sin_port = htons(port);
	return sin_ipv4;
}

SOCKADDR_IN6	addr_ipv6(unsigned int port)
{
	SOCKADDR_IN6	sin_ipv6;
	
	sin_ipv6.sin6_family = AF_INET6;
	sin_ipv6.sin6_addr = in6addr_any;
	sin_ipv6.sin6_port = htons(port);
	return sin_ipv6;
}

void	ircserv(unsigned int port, std::string password)
{
	Socket			sock(port, password);
	int				clientfdIPv4;
	int				clientfdIPv6;
	fd_set 			readfds;
    int 			maxfd;
	
	maxfd = std::max(sock._sockfdIPv4, sock._sockfdIPv6) + 1;
    while (true)
	{
        FD_ZERO(&readfds);
        FD_SET(sock._sockfdIPv4, &readfds);
        FD_SET(sock._sockfdIPv6, &readfds);

        if (select(maxfd, &readfds, NULL, NULL, NULL) == -1)
            throw std::runtime_error(static_cast<std::string>("select(): ") + std::strerror(errno));

        if (FD_ISSET(sock._sockfdIPv4, &readfds))
		{
            clientfdIPv4 = accept(sock._sockfdIPv4, (SOCKADDR *)&sock._sinIPv4, &sock._addrlenIPv4);
			while (true)
				std::cout << get_next_line(clientfdIPv4);
        }

        if (FD_ISSET(sock._sockfdIPv6, &readfds))
		{
            clientfdIPv6 = accept(sock._sockfdIPv6, (SOCKADDR *)&sock._sinIPv6, &sock._addrlenIPv6);
			while (true)
				std::cout << get_next_line(clientfdIPv6);
        }
    }
}

/* ************************************************************************** */
