/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:42:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 15:03:57 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
	#define SERVER_HPP
	#include "tools.hpp"

/* ************************************************************************** */

class Server
{
	public:
		Server(unsigned int port, std::string password);
		~Server();

		bool	init();
		void	closeSocket();
		
		std::string			getPassword() const;
		SOCKET				&getSocket();
		Sockaddr_in6		&getSin6();

	private:
		Server();
		Server(const Server &copy);
		Server	&operator=(const Server &copy);

		bool				initSocket();
		bool				initBind();
		bool				initListen();

		const unsigned int	_port;
		const std::string	_password;
		SOCKET				_socket;
		Sockaddr_in6		_sin6;
};

/* ************************************************************************** */

#endif
