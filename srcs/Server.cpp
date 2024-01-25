/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:49:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 16:19:13 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* COMPULSORY MEMBERS OF THE ORTHODOX CANONICAL CLASS *********************** */

Server::Server() : _port(0), _password("")
{	/* PRIVATE */
}

Server::Server(const Server &copy) : _port(0), _password("")
{	/* PRIVATE */
	*this = copy;
}

Server	&Server::operator=(const Server &copy)
{	/* PRIVATE */
	(void)	copy;
	return	*this;
}

Server::~Server()
{
	this->closeSocket();
}

/* ADDITIONNAL CONSTRUCTORS ************************************************* */

Server::Server(unsigned int port, string_t password) : _port(port), _password(password)
{
	this->sin6.sin6_family = AF_INET6;
	this->sin6.sin6_addr = in6addr_any;
	this->sin6.sin6_port = htons(this->_port);
	this->sock = -1;
}

/* OTHER ******************************************************************** */

bool	Server::init()
{
	if (!this->initSocket() || !this->initBind() || !this->initListen())
	{
		this->closeSocket(); 
		return false;
	}
	return true;
}

void	Server::closeSocket()
{
	if (this->sock != -1)
		close(this->sock);
	this->sock = -1;
}

/* GETTERS ****************************************************************** */
	
string_t	Server::getPassword() const
{
	return this->_password;
}

/* INITIALISERS ************************************************************* */

bool	Server::initSocket()
{	/* PRIVATE */
	this->sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (this->sock == -1)
		return printError("socket"), false;
	return true;
}

bool	Server::initBind()
{	/* PRIVATE */
	if (this->sock == -1 || bind(this->sock, (sockaddr_t *)&(this->sin6), sizeof(this->sin6)) == -1)
		return printError("bind"), false;
	return true;
}

bool	Server::initListen()
{	/* PRIVATE */
	if (this->sock == -1 || listen(this->sock, SOMAXCONN) == -1)
		return printError("listen"), false;
	return true;
}

/* ************************************************************************** */
