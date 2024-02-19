/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/19 23:44:20 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"
#include "tools.hpp"
#include "timeout.hpp"
#include "Channel.hpp"

/* ************************************************************************** */

int	main(int argc, char **argv)
{
	int				port;
	string_t		password;

	if (argc == 3)
	{
		port = portParsing(argv[1]);
		if (port == -1)
			return cerr << "Error: invalid port. [" << MIN_PORT << " - " << MAX_PORT << "]" << '\n', 1;
		password = argv[2];
	}
	else if (argc == 2)
	{
		port = 0;
		password = argv[1];
	}
	else
		return cerr << "Usage: ./" << EXECUTABLE << " [port] <password>" << '\n', 1;
	if (password.length() == 0)
		return cerr << "Error: password cannot be empty" << '\n', 1;
	g_servername = "" + getMyHostname();
	g_serversion = "0.1";
	return !irc_serv(port, password);
}

bool	irc_serv(unsigned int port, string_t password)
{
	pthread_t	thread_connections;
	pthread_t	thread_timeout;
	pollfd_t	pollfds[MAX_CLIENTS + 1];
	Client		clients[MAX_CLIENTS + 1];
	
	if (!Server::init(port, password))
		return false;
    bzero(pollfds, sizeof(pollfds));
    bzero(clients, sizeof(clients));
	pollfds[0].fd = Server::sock;
    pollfds[0].events = POLLIN;

	g_pollfds = pollfds;
	g_clients = clients;
	
	cout << "----------------------------------------" << '\n';
	cout << "Launching " << RED << g_servername << NC << "..." << '\n';
	
	if (pthread_create(&thread_connections, NULL, connections, &clients) != 0)
    	return printError("pthread_create(&thread_connections, ...)"), false;
	if (pthread_create(&thread_timeout, NULL, timeout, &clients) != 0)
    	return printError("pthread_create(&thread_timeout, ...)"), false;

	cout << "Port: " RED << Server::getPort() << NC ", Password: " RED << password << NC << '\n';
	cout << "Created on " RED << formatTime(Server::launchTime) << NC << '\n';
	cout << "Version: " RED << g_serversion << NC << '\n';
	cout << "----------------------------------------" << '\n';
	
	pthread_join(thread_timeout, NULL);
	pthread_join(thread_connections, NULL);
	Server::closeSocket();
	return true;
}

/* ************************************************************************** */

int	portParsing(string_t str)
{
	int		nbr;
	char	*ptr;

	nbr = std::strtod(str.c_str(), &ptr);
	if (nbr < MIN_PORT || nbr > MAX_PORT || ptr != (str.c_str() + str.length()))
		return -1;
	return nbr;	
}

/* GLOBALS ****************************************************************** */

Client						*g_clients = 0;
pollfd_t					*g_pollfds = 0;

std::map<string_t, Channel>	g_channels;
string_t					g_servername;
string_t					g_serversion;
bool 						g_endOfProgram = false;
pthread_mutex_t				g_endOfProgram_mutex;

/* ************************************************************************** */
