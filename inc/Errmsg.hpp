/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errmsg.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:11:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 12:45:25 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRMSG_HPP
	#define ERRMSG_HPP
	
	#include <cerrno>
	#include <string>
	#include <iostream>
	#include <sstream>
	#include <map>

/* ************************************************************************** */

	/* socket() ************************************************************* */

	#define SOCKET_EACCES			"Permission to create a socket of the specified type and/or protocol is denied."
	#define SOCKET_EAFNOSUPPORT		"The implementation does not support the specified address family."
	#define SOCKET_EINVAL			"Unknown protocol, or protocol family not available. / Invalid flags in type."
	#define SOCKET_EMFILE			"The per-process limit on the number of open file descriptors has been reached."
	#define SOCKET_ENFILE			"The system-wide limit on the total number of open files has been reached."
	#define SOCKET_ENOBUFS			"Insufficient memory is available. The socket cannot be created until sufficient resources are freed."
	#define SOCKET_ENOMEM			"Insufficient memory is available. The socket cannot be created until sufficient resources are freed."
	#define SOCKET_EPROTONOSUPPORT	"The protocol type or the specified protocol is not supported within this domain."

	/* bind() *************************************************************** */
	
	#define BIND_EACCES			"The address is protected, and the user is not the superuser."
	#define BIND_EADDRINUSE		"The given address is already in use."
	#define BIND_EBADF			"sockfd is not a valid file descriptor."
	#define BIND_EINVAL			"The socket is already bound to an address. / addrlen is wrong, or addr is not a valid address for this socket's domain."
	#define BIND_ENOTSOCK		"The file descriptor sockfd does not refer to a socket."
	#define BIND_EACCESS		"Search permission is denied on a component of the path prefix.  (See also  path_resolution(7).)"
	#define BIND_EADDRNOTAVAIL	"A nonexistent interface was requested or the requested address was not local."
	#define BIND_EFAULT			"addr points outside the user's accessible address space."
	#define BIND_ELOOP			"Too many symbolic links were encountered in resolving addr."
	#define BIND_ENAMETOOLONG	"addr is too long."
	#define BIND_ENOENT			"A component in the directory prefix of the socket pathname does not exist."
	#define BIND_ENOMEM			"Insufficient kernel memory was available."
	#define BIND_ENOTDIR		"A component of the path prefix is not a directory."
	#define BIND_EROFS			"he socket inode would reside on a read-only filesystem."

/* ************************************************************************** */

class Errmsg
{
	private:
		Errmsg();
		Errmsg(const Errmsg &copy);
		Errmsg &operator=(const Errmsg &copy);
		~Errmsg();

	public:
		static std::string	socket(int errnbr);
		static std::string	bind(int errnbr);
};

/* ************************************************************************** */

#endif
