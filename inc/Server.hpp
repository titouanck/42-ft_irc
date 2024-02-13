/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:42:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/13 13:22:22 by tchevrie         ###   ########.fr       */
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
		std::time_t			getLaunchTime() const;

		socket_t			sock;
		sockaddr_in6_t		sin6;
	
	private:
		Server();
		Server(const Server &copy);
		Server &operator=(const Server &copy);

		bool				initSocket();
		bool				initBind();
		bool				initListen();

		const unsigned int	_port;
		const string_t		_password;
		const std::time_t	_launchTime;
};

/* ************************************************************************** */

#endif
