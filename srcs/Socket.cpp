/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:49:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 21:43:11 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

/* PUBLIC ******************************************************************* */

Socket::Socket(unsigned int port, std::string password) : _port(port), _password(password)
{
	this->_sinIPv4.sin_family = AF_INET;
	this->_sinIPv4.sin_addr.s_addr = INADDR_ANY;
	this->_sinIPv4.sin_port = htons(port);

	this->_sinIPv6.sin6_family = AF_INET6;
	this->_sinIPv6.sin6_addr = in6addr_any;
	this->_sinIPv6.sin6_port = htons(port + 1);

	this->_sockfdIPv4 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	this->_sockfdIPv6 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

	try
	{
		this->s_socket();	
		this->s_bind();	
	}
	catch (...)
	{
		throw ;
	}
}

Socket::~Socket()
{
}

/* ************************************************************************** */

void	Socket::s_socket()
{
	std::string	errmsg;

	this->_sockfdIPv4 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_sockfdIPv4 == -1)
	{
		errmsg = "socket() IPv4: ";
		throw std::runtime_error(errmsg + std::strerror(errno));
	}
	this->_sockfdIPv6 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (this->_sockfdIPv6 == -1)
	{
		errmsg = "socket() IPv6: ";
		close(this->_sockfdIPv4);
		throw std::runtime_error(errmsg + std::strerror(errno));
	}
}

void	Socket::s_bind()
{
	std::string	errmsg;

	if (bind(this->_sockfdIPv4, (SOCKADDR *)&(this->_sinIPv4), sizeof(this->_sinIPv4)) == -1)
		errmsg = "bind() IPv4: ";
	else if (bind(this->_sockfdIPv6, (SOCKADDR *)&(this->_sinIPv6), sizeof(this->_sinIPv6)) == -1)
		errmsg = "bind() IPv6: ";
	else
		return ;
	close(this->_sockfdIPv4);
	close(this->_sockfdIPv6);
	throw std::runtime_error(errmsg + std::strerror(errno));
}

void	Socket::s_listen()
{
	std::string	errmsg;

	if (listen(this->_sockfdIPv4, 2) == -1)
		errmsg = "listen() IPv4:";
	else if (listen(this->_sockfdIPv6, 2) == -1)
		errmsg = "listen() IPv6:";
	else
		return ;
	close(this->_sockfdIPv4);
	close(this->_sockfdIPv6);
	throw std::runtime_error(errmsg + std::strerror(errno));
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
