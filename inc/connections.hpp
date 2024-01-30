/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:53:26 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 17:03:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTIONS_HPP
	#define CONNECTIONS_HPP
	
	#include "tools.hpp"
	#include "Server.hpp"

/* ************************************************************************** */

void	removeConn(Client &client);
void	handleConn(Client *clients);

/* ************************************************************************** */

#endif