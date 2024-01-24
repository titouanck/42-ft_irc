/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:46:00 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 09:54:39 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

/* ************************************************************************** */

void	printError(std::string str)
{
	std::cout << "Error in " << str << ": " << std::strerror(errno) << '\n';
}

std::string	getHostIPv6(Sockaddr_in6 address)
{
	char 	IPv6[INET6_ADDRSTRLEN];

	if (inet_ntop(AF_INET6, &(address.sin6_addr), IPv6, INET6_ADDRSTRLEN) != NULL)
		return IPv6;
	else
		return "::";
}

std::string	getHostName(Sockaddr_in6 addr)
{
	// (void) address;
	
	//    struct sockaddr_in6 addr;
    std::memset(&addr, 0, sizeof(addr));

    // Set the IP address and port
    addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::ff:192.168.56.1", &addr.sin6_addr); // Example IPv6 address
    addr.sin6_port = htons(8080); // Example port

    // Use getnameinfo to convert the sockaddr structure to a human-readable format
    char host[NI_MAXHOST], service[NI_MAXSERV];
    int result = getnameinfo((struct sockaddr*)&addr, sizeof(addr), host, NI_MAXHOST, service, NI_MAXSERV, 0);

    if (result == 0) {
        std::cout << "Host: " << host << ", Service: " << service << std::endl;
    } else {
        std::cerr << "getnameinfo failed: " << gai_strerror(result) << std::endl;
    }

	return "";
	
	
	// // std::string	IPv6;
	// // int 		port;
	// char		host[NI_MAXHOST];
	// char		service[NI_MAXSERV];
    // int 		result;
	
	// // (void)	IPv6;
	// // (void)	port;
	// // IPv6 = getHostIPv6(address);
	// // port = address.sin6_port;
    // std::memset(&address, 0, sizeof(address));
	// address.sin6_family = AF_INET6;
	// inet_pton(AF_INET6, "::ffff:62.210.33.113", &address.sin6_addr); 
    // address.sin6_port = htons(8080); // Example port
	// result = getnameinfo((struct sockaddr*)&address, sizeof(address), host, NI_MAXHOST, service, NI_MAXSERV, 0);

	// if (result == 0)
	// 	std::cout << "Host: " << host << ", Service: " << service << std::endl;
	// else
	// 	std::cerr << "getnameinfo failed: " << gai_strerror(result) << std::endl;
	// return "";
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/* ************************************************************************** */
