/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:46:00 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/12 15:27:33 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.hpp"

/* ************************************************************************** */

void	printError(string_t str)
{
	std::cout << "Error in " << str << ": " << std::strerror(errno) << '\n';
}

bool endsWith(const string_t &str, const string_t &suffix)
{
    if (str.length() < suffix.length())
        return false;
    else
	    return str.substr(str.length() - suffix.length()) == suffix;
}

string_t   lTrim(string_t str)
{
    std::string::size_type first;
    
    first = str.find_first_not_of(" \t");
    if (first == std::string::npos) // If the string is all whitespace
        return "";
    return str.substr(first);
}

string_t   rTrim(string_t str)
{
    std::string::size_type last;
    
    last = str.find_last_not_of(" \t");
    if (last == std::string::npos)
        return "";
    return str.substr(0, last + 1);
}

string_t   trim(string_t str)
{
    str = lTrim(str);
    str = rTrim(str);
    return str;
}

/* ************************************************************************** */
