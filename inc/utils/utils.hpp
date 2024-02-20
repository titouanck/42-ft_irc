/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:48:31 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 00:59:24 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
	#define UTILS_HPP
	#include "types.hpp"

/* ************************************************************************** */

bool		checkStrValidity(string_t str);

bool 		endsWith(const string_t &str, const string_t &suffix);

string_t	formatTime(std::time_t givenTime);

string_t	getMyHostname();

void		printError(string_t str);

string_t	lTrim(string_t str);
string_t	rTrim(string_t str);
string_t	trim(string_t str);

/* ************************************************************************** */

#endif