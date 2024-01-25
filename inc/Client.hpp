/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:29:17 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 15:15:31 by titouanck        ###   ########.fr       */
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

	#define TIMEOUTSEC 50

	class Server;

/* ************************************************************************** */

class Client
{
	public:
		Client();
		Client(const Client &copy);
		Client &operator=(const Client &copy);
		~Client();

		void			setIndex(unsigned int index);
		void			setIdentity();
		void			setNickname(std::string nickname);
		void			setUsername(std::string username);
		void			setOperator(bool isOp);
		void			beAuthenticated(std::string passphrase);
		void			lockMutex();
		void			unlockMutex();

		unsigned int	getIndex() const;
		std::string		getIp() const;
		std::string		getName() const;
		std::string		getIdentity() const;
		std::string		getNickname() const;
		std::string		getUsername() const;
		std::time_t 	getPingTime() const;
		bool			isPinged() const;
		bool			isOperator() const;
		bool			isAuthenticated() const;

		static Server	*server;
		static Pollfd	*pollfds;
		Sockaddr_in6	addr;
		socklen_t		len;

	private:
		unsigned int	_index;
		char			_ip[INET6_ADDRSTRLEN];
		char			_name[NI_MAXHOST];
		std::string		_identity;
		std::string		_nickname;
		std::string		_username;
		std::time_t 	_pingTime;
		bool			_pinged;
		bool			_operator;
		bool			_authenticated;
		pthread_mutex_t	_mutex;
};

/* ************************************************************************** */

#endif
