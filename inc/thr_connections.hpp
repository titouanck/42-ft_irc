/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_connections.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:14:09 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 18:16:49 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THR_CONNECTIONS_HPP
	#define THR_CONNECTIONS_HPP
	#include "typedef.hpp"
	#include "connections.hpp"

/* ************************************************************************** */

bool 	thr_connections(pollfd_t *pollfds, Client *clients);

/* ************************************************************************** */

#endif
