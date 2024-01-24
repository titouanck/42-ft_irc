/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:48:31 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 08:47:14 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
	#define TOOLS_HPP
	#include <string>
	#include <iostream>
	#include <errno.h>
	#include <cstring>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <poll.h>
	#include <string>
	#include <sstream>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>

/* ************************************************************************** */

void		printError(std::string str);
std::string	getHostName(const sockaddr *addr, socklen_t addrlen);

/* ************************************************************************** */

#endif