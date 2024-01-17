/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errmsg.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:41:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 13:49:04 by titouanck        ###   ########.fr       */
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
	oss << errno; 
	return static_cast<std::string>("socket(): errno=") + oss.str();
}

std::string	Errmsg::bind(int errnbr)
{
	static std::map<int, std::string>	msg;
	std::ostringstream					oss;

	if (msg.size() == 0)
	{
		msg[EACCES] 		= BIND_EACCES;
		msg[EADDRINUSE] 	= BIND_EADDRINUSE;
		msg[EBADF] 			= BIND_EBADF;
		msg[EINVAL] 		= BIND_EINVAL;
		msg[ENOTSOCK] 		= BIND_ENOTSOCK;
		msg[EADDRNOTAVAIL] 	= BIND_EADDRNOTAVAIL;
		msg[EFAULT] 		= BIND_EFAULT;
		msg[ELOOP] 			= BIND_ELOOP;
		msg[ENAMETOOLONG] 	= BIND_ENAMETOOLONG;
		msg[ENOENT] 		= BIND_ENOENT;
		msg[ENOMEM] 		= BIND_ENOMEM;
		msg[ENOTDIR] 		= BIND_ENOTDIR;
		msg[EROFS] 			= BIND_EROFS;
	}
	if (msg.find(errnbr) != msg.end())
		return static_cast<std::string>("bind(): ") + msg[errnbr];
	oss << errno; 
	return static_cast<std::string>("bind(): errno=") + oss.str();
}

/* ************************************************************************** */
