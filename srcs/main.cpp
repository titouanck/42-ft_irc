/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/12 15:15:48 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "tools.hpp"
#include "thr_timeout.hpp"

/* ************************************************************************** */

bool	irc_serv(unsigned int port, string_t password)
{
	Server		server(port, password);
	pollfd_t	pollfds[MAX_CLIENTS + 1];
	Client		clients[MAX_CLIENTS + 1];
	pthread_t	thread_timeout;
	pthread_t	thread_connections;
	
	if (!server.init())
		return false;
    bzero(pollfds, sizeof(pollfds));
    bzero(clients, sizeof(clients));
	pollfds[0].fd = server.sock;
    pollfds[0].events = POLLIN;

	IRC::server  = &server;
	IRC::pollfds = pollfds;
	IRC::clients = clients;
	
	if (pthread_create(&thread_timeout, NULL, thr_timeout, &clients) != 0)
    	return printError("pthread_create(&thread_timeout, ...)"), false;
	if (pthread_create(&thread_connections, NULL, thr_connections, &clients) != 0)
    	return printError("pthread_create(&thread_connections, ...)"), false;

	std::cout << "Port: " << port << '\n';
	std::cout << "Password: " << password << '\n';
	std::cout << "Server started" << '\n';
	pthread_join(thread_connections, NULL);
	pthread_join(thread_timeout, NULL);
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

bool 			endOfProgram = false;
pthread_mutex_t	endOfProgram_mutex;

/* ************************************************************************** */
