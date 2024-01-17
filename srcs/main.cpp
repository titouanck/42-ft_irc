/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 11:31:17 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/* ************************************************************************** */

int	main(int argc, char **argv)
{
	unsigned int	port;
	std::string		password;

	if (argc != 3)
	{
		std::cerr << "usage: ./" << EXECUTABLE << " <port> <password>" << '\n';
		return 1;
	}

	try
	{
		port	 = portParsing(argv[1]);
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

unsigned int	portParsing(std::string str)
{
	int		nbr;
	char	*ptr;

	nbr = std::strtod(str.c_str(), &ptr);
	if (nbr < 0 || nbr > 65535 || ptr != (str.c_str() + str.length()))
		throw std::runtime_error("Error: invalid port. [0 - 65535]");
	return static_cast<unsigned int>(nbr);	
}

std::string	passwordParsing(std::string str)
{
	if (str.length() == 0)
		throw std::runtime_error("Error: invalid password");

	return str;	
}

/* ************************************************************************** */
