/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/18 14:03:04 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include "ircserv.hpp"
#include <stdio.h>
#include "get_next_line.h"

/* ************************************************************************** */

bool	ircserv(unsigned int port, std::string password)
{
	(void)				port;
	(void)				password;
	Socket				sock(port, password);
	int					acceptfd;
	socklen_t			addrlen;

	bind(sock._sockfd, (SOCKADDR *)&(sock._sin6), sizeof(sock._sin6));
	listen(sock._sockfd, 2);
	acceptfd = accept(sock._sockfd, (SOCKADDR *)&sock._sin6, &addrlen);
	std::cout << "AFTER ACCEPT\n";
	while (true)
	{
		std::cout << get_next_line(acceptfd);
	}
	return true;
}

/* ************************************************************************** */
