/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:48:31 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/13 21:43:55 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
	#define TOOLS_HPP
	#include "Client.hpp"

/* ************************************************************************** */

void		printError(string_t str);
bool 		endsWith(const string_t &str, const string_t &suffix);
string_t	lTrim(string_t str);
string_t	rTrim(string_t str);
string_t	trim(string_t str);
string_t	formatTime(std::time_t givenTime);
string_t	getMyHostname();
bool		checkStrValidity(string_t str);

/* ************************************************************************** */

#endif