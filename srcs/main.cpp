/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 18:16:24 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/* ************************************************************************** */

bool	irc_serv(unsigned int port, string_t password)
{
	Server		server(port, password);
	pollfd_t	pollfds[MAX_CLIENTS + 1];
	Client		clients[MAX_CLIENTS + 1];
	
	if (!server.init())
		return false;
    bzero(pollfds, sizeof(pollfds));
    bzero(clients, sizeof(clients));
	pollfds[0].fd = server.sock;
    pollfds[0].events = POLLIN;

	Client::server  = &server;
	Client::pollfds = pollfds;
	thr_connections(pollfds, clients);
	
	server.closeSocket();
	return true;
}

int	main(int argc, char **argv)
{
	int				port;
	string_t		password;

	if (argc != 3)
		return std::cerr << "Usage: ./" << EXECUTABLE << " <port> <password>" << '\n', 1;
	port = portParsing(argv[1]);
	if (port == -1)
		return std::cerr << "Error: invalid port. [1024 - 65535]" << '\n', 1;
	password = argv[2];
	if (password.length() == 0)
		return std::cerr << "Error: password cannot be empty" << '\n', 1;
	return !irc_serv(port, password);
}

/* ************************************************************************** */

int	portParsing(string_t str)
{
	int		nbr;
	char	*ptr;

	nbr = std::strtod(str.c_str(), &ptr);
	if (nbr < 1024 || nbr > 65535 || ptr != (str.c_str() + str.length()))
		return -1;
	return nbr;	
}

/* ************************************************************************** */
