/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:46:00 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 17:57:54 by titouanck        ###   ########.fr       */
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

/* ************************************************************************** */
