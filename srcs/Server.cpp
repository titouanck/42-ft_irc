/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:49:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 21:17:04 by titouanck        ###   ########.fr       */
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

Server::Server(unsigned int port, std::string password) : _port(port), _password(password)
{
	this->_sin6.sin6_family = AF_INET6;
	this->_sin6.sin6_addr = in6addr_any;
	this->_sin6.sin6_port = htons(this->_port);
	this->_socket = -1;
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
	if (this->_socket != -1)
		close(this->_socket);
	this->_socket = -1;
}

/* GETTERS ****************************************************************** */
	
SOCKET	&Server::getSocket()
{
	return this->_socket;
}

Sockaddr_in6	&Server::getSin6()
{
	return this->_sin6;
}

/* INITIALISERS ************************************************************* */

bool	Server::initSocket()
{	/* PRIVATE */
	this->_socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (this->_socket == -1)
		return printError("socket"), false;
	return true;
}

bool	Server::initBind()
{	/* PRIVATE */
	if (this->_socket == -1 || bind(this->_socket, (Sockaddr *)&(this->_sin6), sizeof(this->_sin6)) == -1)
		return printError("bind"), false;
	return true;
}

bool	Server::initListen()
{	/* PRIVATE */
	if (this->_socket == -1 || listen(this->_socket, SOMAXCONN) == -1)
		return printError("listen"), false;
	return true;
}

/* ************************************************************************** */
