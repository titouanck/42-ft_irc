/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:29:17 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/12 14:18:17 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
	#define CLIENT_HPP
	#include "IRC.hpp"

	class Server;

/* ************************************************************************** */

class Client
{
	public:
		Client();
		Client(const Client &copy);
		Client &operator=(const Client &copy);
		~Client();

		void			PASS(string_t passphrase);
		void			setIndex(unsigned int index);
		void			setIdentity();
		void			setOperator(bool isOp);
		void			NICK(string_t nickname);
		void			USER(string_t content);
		// void			setUsername(string_t username);
		// void			setRealname(string_t realname);
		// void			setHostname(string_t hostname);
		void			lockMutex();
		void			unlockMutex();

		

		unsigned int	getIndex() const;
		string_t		getIp() const;
		string_t		getName() const;
		string_t		getIdentity() const;
		std::time_t 	getPingTime() const;
		bool			isPinged() const;
		bool			isOperator() const;
		bool			isAuthenticated() const;
		string_t		getNickname() const;
		string_t		getUsername() const;
		string_t		getRealname() const;

		static Server	*server;
		static pollfd_t	*pollfds;
		sockaddr_in6_t	addr;
		socklen_t		len;

	private:
		unsigned int	_index;
		char			_ip[INET6_ADDRSTRLEN];
		char			_name[NI_MAXHOST];
		string_t		_identity;
		std::time_t 	_pingTime;
		bool			_pinged;
		bool			_operator;
		bool			_authenticated;
		string_t		_nickname;
		string_t		_username;
		string_t		_realname;
		pthread_mutex_t	_mutex;
};

/* ************************************************************************** */

#endif
