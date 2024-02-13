/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/13 17:13:22 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "tools.hpp"
#include "thr_timeout.hpp"

/* ************************************************************************** */

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

	g_servername = "ircserv." + getMyHostname();
	g_serversion = "0.1";
	return !irc_serv(port, password);
}

bool	irc_serv(unsigned int port, string_t password)
{
	pthread_t	thread_connections;
	pthread_t	thread_timeout;
	Server		server(port, password);
	pollfd_t	pollfds[MAX_CLIENTS + 1];
	Client		clients[MAX_CLIENTS + 1];
	
	if (!server.init())
		return false;
    bzero(pollfds, sizeof(pollfds));
    bzero(clients, sizeof(clients));
	pollfds[0].fd = server.sock;
    pollfds[0].events = POLLIN;

	g_server  = &server;
	g_pollfds = pollfds;
	g_clients = clients;
	
	std::cout << "----------------------------------------" << '\n';
	std::cout << "Launching " << RED << g_servername << NC << "..." << '\n';
	
	if (pthread_create(&thread_connections, NULL, thr_connections, &clients) != 0)
    	return printError("pthread_create(&thread_connections, ...)"), false;
	if (pthread_create(&thread_timeout, NULL, thr_timeout, &clients) != 0)
    	return printError("pthread_create(&thread_timeout, ...)"), false;

	std::cout << "Port: " RED << port << NC ", Password: " RED << password << NC << '\n';
	std::cout << "Created on " RED << formatTime(server.getLaunchTime()) << NC << '\n';
	std::cout << "Version: " RED << g_serversion << NC << '\n';
	std::cout << "----------------------------------------" << '\n';
	
	pthread_join(thread_timeout, NULL);
	pthread_join(thread_connections, NULL);
	server.closeSocket();
	return true;
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

/* GLOBALS ****************************************************************** */

Server			*g_server  = 0;
Client			*g_clients = 0;
pollfd_t		*g_pollfds = 0;

string_t		g_servername;
string_t		g_serversion;
bool 			g_endOfProgram = false;
pthread_mutex_t	g_endOfProgram_mutex;

/* ************************************************************************** */
