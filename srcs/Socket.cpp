/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:49:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/18 14:05:41 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

/* PUBLIC ******************************************************************* */

Socket::Socket(unsigned int port, std::string password) : _port(port), _password(password)
{
	this->_sin6.sin6_family = AF_INET6;
	this->_sin6.sin6_addr = in6addr_any;
	this->_sin6.sin6_port = htons(port);

	if (!this->initSocket() || !this->initBind() || !this->initListen())
	{
		this->closeAll();
		throw std::runtime_error(std::strerror(errno));
	}
}

Socket::~Socket()
{
}

/* ************************************************************************** */

bool	Socket::initSocket()
{
	this->_sockfd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (this->_sockfd == -1)
		return false;

	return true;
}

bool	Socket::initBind()
{
	if (this->_sockfd == -1 || bind(this->_sockfd, (SOCKADDR *)&(this->_sin6), sizeof(this->_sin6)) == -1)
		return false;
	return true;
}

bool	Socket::initListen()
{
	if (this->_sockfd == -1 || listen(this->_sockfd, 2) == -1)
		return false;
	return true;
}

/* ************************************************************************** */

void	Socket::closeSocket()
{
	if (this->_sockfd != -1)
		close(this->_sockfd);
	this->_sockfd = -1;
}

/* PRIVATE ****************************************************************** */

Socket::Socket() : _port(0), _password("")
{
}

Socket::Socket(const Socket &copy) : _port(0), _password("")
{
	*this = copy;
}

Socket	&Socket::operator=(const Socket &copy)
{
	(void)	copy;
	return	*this;
}

/* ************************************************************************** */
