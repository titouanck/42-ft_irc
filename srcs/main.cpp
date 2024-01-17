/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 17:55:01 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/* ************************************************************************** */

int	main(int argc, char **argv)
{
	unsigned int	port;
	std::string		password;

	try
	{
		checkArgs(argc);
		port = portParsing(argv[1]);
		password = passwordParsing(argv[2]);
		ircserv(port, password);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}

/* ************************************************************************** */

void	checkArgs(int argc)
{
	if (argc != 3)
		throw std::runtime_error(static_cast<std::string>("usage: ./") + EXECUTABLE + " <port> <password>");
}

unsigned int	portParsing(std::string str)
{
	int		nbr;
	char	*ptr;

	nbr = std::strtod(str.c_str(), &ptr);
	if (nbr < 1024 || nbr > 65535 || ptr != (str.c_str() + str.length()))
		throw std::runtime_error("Error: invalid port. [1024 - 65535]");
	return static_cast<unsigned int>(nbr);	
}

std::string	passwordParsing(std::string str)
{
	if (str.length() == 0)
		throw std::runtime_error("Error: invalid password");

	return str;	
}

/* ************************************************************************** */
