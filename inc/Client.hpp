/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:29:17 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 21:35:52 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
	#define CLIENT_HPP
	
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
	
	typedef int					SOCKET;
	typedef struct sockaddr 	Sockaddr;
	typedef struct sockaddr_in6	Sockaddr_in6;
	typedef struct sockaddr_in	Sockaddr_in;
	typedef struct pollfd		Pollfd;

	#define TIMEOUTSEC 10

/* ************************************************************************** */

class Client
{
	public:
		Client();
		Client(const Client &copy);
		Client &operator=(const Client &copy);
		~Client();

		void		setIdentity();
		void		setNickname(std::string nickname);
		std::string	getIp() const;
		std::string	getName() const;
		std::string	getIdentity() const;
		std::time_t getPingTime() const;
		bool		isPinged() const;

		Sockaddr_in6	addr;
		socklen_t		len;

	private:
		char			_ip[INET6_ADDRSTRLEN];
		char			_name[NI_MAXHOST];
		std::string		_identity;
		std::string		_nickname;
		std::time_t 	_pingTime;
		bool			_pinged;
};

/* ************************************************************************** */

#endif
