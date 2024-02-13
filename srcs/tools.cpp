/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:46:00 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/13 21:47:02 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

/* ************************************************************************** */

void	printError(string_t str)
{
	std::cout << "Error in " << str << ": " << std::strerror(errno) << '\n';
}

bool	endsWith(const string_t &str, const string_t &suffix)
{
	if (str.length() < suffix.length())
		return false;
	else
		return str.substr(str.length() - suffix.length()) == suffix;
}

string_t	lTrim(string_t str)
{
	std::string::size_type first;

	first = str.find_first_not_of(" \t");
	if (first == std::string::npos) // If the string is all whitespace
		return "";
	return str.substr(first);
}

string_t	rTrim(string_t str)
{
	std::string::size_type last;

	last = str.find_last_not_of(" \t");
	if (last == std::string::npos)
		return "";
	return str.substr(0, last + 1);
}

string_t	trim(string_t str)
{
	str = lTrim(str);
	str = rTrim(str);
	return str;
}

string_t	formatTime(std::time_t givenTime)
{
	std::tm	*now;
    char 	buffer[80];
	
	now = std::localtime(&givenTime);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now);
	return buffer;
}

string_t	getMyHostname()
{
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0)
		return hostname;
    return "";
}

bool	checkStrValidity(string_t str)
{
	size_t	len;

	len = str.length();
	for (size_t i = 0; i < len; i++)
	{
		if (!isalnum(str[i]) && str[i] != '-' && str[i] != '_')
			return false;
	}
	return true;
}

/* ************************************************************************** */
