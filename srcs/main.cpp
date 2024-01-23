/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/23 20:44:13 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/* ************************************************************************** */

int	main(int argc, char **argv)
{
	int				port;
	std::string		password;

	if (argc != 3)
		return std::cerr << "Usage: ./" << EXECUTABLE << " <port> <password>" << '\n', 1;
	port = portParsing(argv[1]);
	if (port == -1)
		return std::cerr << "Error: invalid port. [1024 - 65535]" << '\n', 1;
	password = argv[2];
	if (password.length() == 0)
		return std::cerr << "Error: password cannot be empty" << '\n', 1;
	return !ircserv(port, password);
}

/* ************************************************************************** */

int	portParsing(std::string str)
{
	int		nbr;
	char	*ptr;

	nbr = std::strtod(str.c_str(), &ptr);
	if (nbr < 1024 || nbr > 65535 || ptr != (str.c_str() + str.length()))
		return -1;
	return nbr;	
}

/* ************************************************************************** */
