/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:42:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 21:38:03 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
	#define SOCKET_HPP
	#include <string>
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
	
	typedef struct sockaddr SOCKADDR;
	typedef struct sockaddr_in	SOCKADDR_IN;
	typedef struct sockaddr_in6	SOCKADDR_IN6;

/* ************************************************************************** */

class Socket
{
	public:
		Socket(unsigned int port, std::string password);
		~Socket();

		void	s_socket();
		void	s_bind();
		void	s_listen();

		int					_sockfdIPv4;
		int					_sockfdIPv6;
		socklen_t			_addrlenIPv4;
		socklen_t			_addrlenIPv6;
		SOCKADDR_IN			_sinIPv4;
		SOCKADDR_IN6		_sinIPv6;

	private:
		Socket();
		Socket(const Socket &copy);
		Socket	&operator=(const Socket &copy);

		const unsigned int	_port;
		const std::string	_password;
};

/* ************************************************************************** */

#endif
