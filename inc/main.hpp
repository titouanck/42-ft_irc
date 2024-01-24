/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/24 14:08:30 by titouanck        ###   ########.fr       */
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

	#ifndef EXECUTABLE
		#define EXECUTABLE ircserv
	#endif

/* ************************************************************************** */

void			checkArgs(int argc);
int				portParsing(std::string str);
std::string		passwordParsing(std::string str);

/* ************************************************************************** */

#endif
