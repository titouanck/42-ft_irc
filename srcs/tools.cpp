/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:46:00 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 11:09:04 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

/* ************************************************************************** */

void	printError(std::string str)
{
	std::cout << "Error in " << str << ": " << std::strerror(errno) << '\n';
}

std::string	getHostIp(Sockaddr_in6 addr)
{
	char 		ip[INET6_ADDRSTRLEN];

	inet_ntop(AF_INET6, &(addr.sin6_addr), ip, INET6_ADDRSTRLEN);
	return ip;
}

std::string	getHostName(Sockaddr_in6 addr)
{
    char	host[NI_MAXHOST];
	
	if (getnameinfo((struct sockaddr*)&addr, sizeof(addr), host, NI_MAXHOST, NULL, 0, 0) == 0)
		return host;
	else
		return "";
}

std::string	getHostInfo(Sockaddr_in6 addr)
{
	std::string			ip;
	std::string			name;
	std::ostringstream	oss;

	ip = getHostIp(addr);
	name = getHostName(addr);

	if (ip.compare(name) != 0 && name.length() > 0)
	{
		if (ip.length() >= 7 && ip.substr(0, 7) == "::ffff:")
			ip = ip.substr(7);
		oss << name;
		// oss << name << " (" << ip << ")";
	}
	else
	{
		if (ip.length() >= 7 && ip.substr(0, 7) == "::ffff:")
			ip = ip.substr(7);
		oss << ip;
	}
	return oss.str();
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/* ************************************************************************** */
