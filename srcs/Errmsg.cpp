/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errmsg.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:41:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 13:02:33 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Errmsg.hpp"

/* PRIVATE ****************************************************************** */

Errmsg::Errmsg()
{
}

Errmsg::Errmsg(const Errmsg &copy)
{
	*this = copy;
}

Errmsg &Errmsg::operator=(const Errmsg &copy)
{
	(void)	copy;
	return	*this;
}

Errmsg::~Errmsg()
{
}

/* PUBLIC ******************************************************************* */

std::string	Errmsg::socket(int errnbr)
{
	static std::map<int, std::string>	msg;
	std::ostringstream					oss;

	if (msg.size() == 0)
	{
		msg[EACCES] 			= SOCKET_EACCES;
		msg[EAFNOSUPPORT]		= SOCKET_EAFNOSUPPORT;
		msg[EINVAL]				= SOCKET_EINVAL;
		msg[EMFILE]				= SOCKET_EMFILE;
		msg[ENFILE]				= SOCKET_ENFILE;
		msg[ENOBUFS]			= SOCKET_ENOBUFS;
		msg[ENOMEM]				= SOCKET_ENOMEM;
		msg[EPROTONOSUPPORT]	= SOCKET_EPROTONOSUPPORT;
	}

	if (msg.find(errnbr) != msg.end())
		return static_cast<std::string>("socket(): ") + msg[errnbr];
	else
	{
		oss << errno; 
		return static_cast<std::string>("socket(): errno=") + oss.str();
	}
}

/* ************************************************************************** */
