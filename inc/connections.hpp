/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:53:26 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 11:28:06 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTIONS_HPP
	#define CONNECTIONS_HPP
	
	#include "tools.hpp"
	#include "Server.hpp"

	typedef unsigned char	connStatus;

/* ************************************************************************** */

void	removeConn(Pollfd &pollfd, Client &client, int nbr);
void	handleConn(Server &server, Pollfd (&pollfds)[MAX_CLIENTS + 1], Client (&clients)[MAX_CLIENTS + 1]);

/* ************************************************************************** */

#endif
