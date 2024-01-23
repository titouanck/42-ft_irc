/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:42:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/23 20:24:47 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
	#define SERVER_HPP
	#include "error.hpp"
	#include <arpa/inet.h>
	#include <poll.h>
	#include <string>
	#include <sstream>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>
	
	typedef int					SOCKET;
	typedef struct sockaddr 	Sockaddr;
	typedef struct sockaddr_in6	Sockaddr_in6;
	typedef struct sockaddr_in	Sockaddr_in;
	typedef struct pollfd		Pollfd;

	typedef struct s_Client
	{
		SOCKET	fd;
		char	NICKNAME[10];
	}			Client;

/* ************************************************************************** */

class Server
{
	public:
		Server(unsigned int port, std::string password);
		~Server();

		bool	init();
		void	closeSocket();
		
		SOCKET			&getSocket();
		Sockaddr_in6	&getSin6();

	private:
		Server();
		Server(const Server &copy);
		Server	&operator=(const Server &copy);

		bool	initSocket();
		bool	initBind();
		bool	initListen();

		const unsigned int	_port;
		const std::string	_password;
		SOCKET				_socket;
		Sockaddr_in6		_sin6;
};

/* ************************************************************************** */

#endif
