/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:13:48 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 14:37:02 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"
#include <stdio.h>

/* ************************************************************************** */

void	ircserv(unsigned int port, std::string password)
{
	(void)				port;
	(void)				password;
	int					sockfd;
	// SOCKADDR_IN			sin = {0};

	errno = 34566;
	// sockfd = socket(AF_INET, SOCK_STREAM, 0);
	sockfd = -1;
	if (sockfd == -1)
	{
		perror("socket()");
		throw std::runtime_error(Errmsg::socket(errno).c_str());
	}
	// sin.sin_addr.s_addr = htonl(INADDR_ANY);
	// sin.sin_family = AF_INET;
	// sin.sin_port = htons(port);
	// if (bind(sockfd, &sin, sizeof(sin)) == -1)
	// 	throw std::runtime_error(Errmsg::bind(errno).c_str());
}

/* ************************************************************************** */
