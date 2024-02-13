/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:54:14 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/12 14:58:04 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_HPP
	#define TYPES_HPP
	
/* INCLUDES ***************************************************************** */

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
	#include <bits/stdc++.h> 

	class Server;
	class Client;

/* DEFINES ****************************************************************** */

	#ifndef EXECUTABLE
		#define EXECUTABLE "ircserv"
	#endif
	#define TIMEOUTSEC 30
	#define MAX_CLIENTS 2
	#define GUEST "anonymous"

/* COLORS ******************************************************************* */

	#define RED "\033[0;31m"
	#define GREEN "\033[0;32m"
	#define ORANGE "\033[0;33m"
	#define BLUE "\033[0;34m"
	#define MAGENTA "\033[35m"
	#define CYAN "\033[36m"
	#define BOLD "\033[1m"
	#define NC "\033[0m"

/* TYPEDEFS ***************************************************************** */

	typedef struct sockaddr 	sockaddr_t;
	typedef struct sockaddr_in6	sockaddr_in6_t;
	typedef struct sockaddr_in	sockaddr_in_t;
	typedef struct pollfd		pollfd_t;
	typedef int					socket_t;
	typedef	std::string			string_t;

/* STRUCTURES *************************************************************** */

	typedef struct s_message
	{
		string_t	command;
		string_t	content;
	}	Message;

	typedef struct s_ircReference
	{
		string_t	numeric;
		string_t	content;
	}	IrcReference;

/* GLOBALS ****************************************************************** */

	extern Server			*g_server;
	extern Client			*g_clients;
	extern pollfd_t			*g_pollfds;

	extern string_t			g_servername;
	extern string_t			g_serversion;
	extern bool 			g_endOfProgram;
	extern pthread_mutex_t	g_endOfProgram_mutex;

/* ************************************************************************** */

#endif
