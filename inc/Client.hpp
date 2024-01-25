/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:29:17 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 18:10:14 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
	#define CLIENT_HPP
	#include "typedef.hpp"

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
		void			setNickname(string_t nickname);
		void			setUsername(string_t username);
		void			setOperator(bool isOp);
		void			beAuthenticated(string_t passphrase);
		void			lockMutex();
		void			unlockMutex();

		unsigned int	getIndex() const;
		string_t		getIp() const;
		string_t		getName() const;
		string_t		getIdentity() const;
		string_t		getNickname() const;
		string_t		getUsername() const;
		std::time_t 	getPingTime() const;
		bool			isPinged() const;
		bool			isOperator() const;
		bool			isAuthenticated() const;

		static Server	*server;
		static pollfd_t	*pollfds;
		sockaddr_in6_t	addr;
		socklen_t		len;

	private:
		unsigned int	_index;
		char			_ip[INET6_ADDRSTRLEN];
		char			_name[NI_MAXHOST];
		string_t		_identity;
		string_t		_nickname;
		string_t		_username;
		std::time_t 	_pingTime;
		bool			_pinged;
		bool			_operator;
		bool			_authenticated;
		pthread_mutex_t	_mutex;
};

/* ************************************************************************** */

#endif
