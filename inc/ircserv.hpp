/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:14:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/18 14:02:09 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
	#define IRCSERV_HPP
	#include <errno.h>
	#include <arpa/inet.h>
	#include <cstring>
	#include <string>
	#include <iostream>
	#include <sstream>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>

	typedef struct sockaddr_storage SOCKADDR_STORAGE;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr_in6 SOCKADDR_IN6;
	typedef struct in_addr IN_ADDR;

/* ************************************************************************** */

bool		ircserv(unsigned int port, std::string password);

/* ************************************************************************** */

#endif
