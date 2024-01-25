/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 16:02:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
	#define MAIN_HPP
	#include <string>
	#include <iostream>
	#include <stdexcept>
	#include <cstdlib>
	#include "ircserv.hpp"
	#include "tools.hpp"

/* ************************************************************************** */

void			checkArgs(int argc);
int				portParsing(string_t str);
string_t		passwordParsing(string_t str);

/* ************************************************************************** */

#endif
