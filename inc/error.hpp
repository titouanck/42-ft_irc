/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:48:31 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/23 19:51:50 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
	#define ERROR_HPP
	#include <string>
	#include <iostream>
	#include <errno.h>
	#include <cstring>

/* ************************************************************************** */

void	printError(std::string str);
void	errorWith(std::string str);

/* ************************************************************************** */

#endif