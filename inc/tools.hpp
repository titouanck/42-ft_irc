/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:48:31 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 11:00:34 by titouanck        ###   ########.fr       */
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
	#include <iostream>
	#include <algorithm>
	#include <cctype>
	#include <string>

	#define RED "\033[0;31m"
	#define BLUE "\033[0;34m"
	#define NC "\033[0m"

	typedef int					SOCKET;
	typedef struct sockaddr 	Sockaddr;
	typedef struct sockaddr_in6	Sockaddr_in6;
	typedef struct sockaddr_in	Sockaddr_in;
	typedef struct pollfd		Pollfd;

/* ************************************************************************** */

void			printError(std::string str);
std::string		getHostIp(Sockaddr_in6 clientAddress);
std::string		getHostName(Sockaddr_in6 address);
std::string		getHostInfo(Sockaddr_in6 addr);
void 			*get_in_addr(struct sockaddr *sa);

/* ************************************************************************** */

#endif