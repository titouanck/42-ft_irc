/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 17:20:10 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"
#include <stdio.h>
#include "get_next_line.h"

/* ************************************************************************** */

void	ircserv(unsigned int port, std::string password)
{
	(void)				port;
	(void)				password;
	int					sockfd;
	SOCKADDR_IN			sin;
	int					acceptfd;
	socklen_t			addrlen;

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == -1)
		throw std::runtime_error(static_cast<std::string>("socket(): ") + std::strerror(errno));
	else
		std::cout << "socket() is OK!" << '\n';
	
	sin.sin_family = AF_INET;
	inet_pton(sin.sin_family, "127.0.0.1", &sin.sin_addr.s_addr);
	sin.sin_port = htons(port);
	if (bind(sockfd, (SOCKADDR *)&sin, sizeof(sin)) == -1)
		throw std::runtime_error(static_cast<std::string>("bind(): ") + std::strerror(errno));
	else
		std::cout << "bind() is OK!" << '\n';

	if (listen(sockfd, 2) == -1)
		throw std::runtime_error(static_cast<std::string>("listen(): ") + std::strerror(errno));
	else
		std::cout << "listen() is OK!" << '\n';

	acceptfd = accept(sockfd, (SOCKADDR *)&sin, &addrlen);
	if (acceptfd == -1)
		throw std::runtime_error(static_cast<std::string>("accept(): ") + std::strerror(errno));
	else
		std::cout << "accept() is OK! | acceptfd=" << acceptfd << " sockfd=" << sockfd << '\n';
	while (true)
	{
		std::cout << get_next_line(acceptfd);
		write(acceptfd, "salut \n", 7);
	}
}

/* ************************************************************************** */
