/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:42:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 16:19:23 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
	#define SERVER_HPP
	#include "tools.hpp"

/* ************************************************************************** */

class Server
{
	public:
		Server(unsigned int port, string_t password);
		~Server();

		bool				init();
		void				closeSocket();
		string_t			getPassword() const;

		socket_t			sock;
		sockaddr_in6_t		sin6;
	
	private:
		bool				initSocket();
		bool				initBind();
		bool				initListen();

		const unsigned int	_port;
		const string_t	_password;

		Server();
		Server(const Server &copy);
		Server	&operator=(const Server &copy);
};

/* ************************************************************************** */

#endif
