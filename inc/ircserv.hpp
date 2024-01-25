/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:14:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 10:16:03 by titouanck        ###   ########.fr       */
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
	#include <iostream>
	#include <cstdlib>
	#include <cstring>
	#include <fcntl.h>
	#include <unistd.h>
	#include "connections.hpp"

	#ifndef EXECUTABLE
		#define EXECUTABLE "ircserv"
	#endif

/* ************************************************************************** */

bool	ircserv(unsigned int port, std::string password);

/* ************************************************************************** */

#endif
