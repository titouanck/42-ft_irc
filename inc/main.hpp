/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/17 12:00:19 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
	#define MAIN_HPP
	#include <string>
	#include <iostream>
	#include <stdexcept>
	#include <cstdlib>
	#include "ircserv.hpp"

	#define RED "\033[0;31m"
	#define BLUE "\033[0;34m"
	#define NC "\033[0m"

/* ************************************************************************** */

unsigned int	portParsing(std::string str);
std::string		passwordParsing(std::string str);

/* ************************************************************************** */

#endif
