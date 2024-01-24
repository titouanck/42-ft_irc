/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:46:00 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 08:53:37 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

/* ************************************************************************** */

void	printError(std::string str)
{
	std::cout << "Error in " << str << ": " << std::strerror(errno) << '\n';
}

std::string	getHostName(const sockaddr *addr, socklen_t addrlen)
{
	char	host[4096];
	
	bzero(host, 4096);
	if (getnameinfo(addr, addrlen, host, sizeof(host), 0, 0, 0) == 0)
		return static_cast<std::string>(host);
	else
		return static_cast<std::string>("");
}

/* ************************************************************************** */
