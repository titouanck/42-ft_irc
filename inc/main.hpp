/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:43:28 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/13 13:57:59 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
	#define MAIN_HPP
	#include "thr_connections.hpp"
	#include "tools.hpp"
	#include "numericReferences.hpp"

/* ************************************************************************** */

int		portParsing(string_t str);
bool	irc_serv(unsigned int port, string_t password);

/* ************************************************************************** */

#endif
