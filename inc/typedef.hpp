/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:54:14 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/30 16:01:16 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_HPP
	#define TYPEDEF_HPP
	
	#include <string>
	#include <iostream>
	#include <errno.h>
	#include <cstring>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <poll.h>
	#include <sstream>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <algorithm>
	#include <cctype>
	#include <ctime>
	#include <sys/time.h>
	#include <stdexcept>
	#include <cstdlib>

/* ************************************************************************** */

	#ifndef EXECUTABLE
		#define EXECUTABLE "ircserv"
	#endif
	#define TIMEOUTSEC 50
	#define MAX_CLIENTS 2
	#define RED "\033[0;31m"
	#define GREEN "\033[0;32m"
	#define ORANGE "\033[0;33m"
	#define BLUE "\033[0;34m"
	#define NC "\033[0m"

/* ************************************************************************** */

	typedef struct sockaddr 	sockaddr_t;
	typedef struct sockaddr_in6	sockaddr_in6_t;
	typedef struct sockaddr_in	sockaddr_in_t;
	typedef struct pollfd		pollfd_t;
	typedef int					socket_t;
	typedef	std::string			string_t;

/* ************************************************************************** */

	class Server;
	class Client;

	typedef struct s_data
	{
		Server		&server;
		Client		(&clients)[MAX_CLIENTS + 1];
		pollfd_t	(&pollfds)[MAX_CLIENTS + 1];
	}	Data;

	typedef struct s_message
	{
		string_t	command;
		string_t	content;
	}	Message;

	extern bool 			EOP;
	extern pthread_mutex_t	EOP_mutex;

/* ************************************************************************** */

#endif
