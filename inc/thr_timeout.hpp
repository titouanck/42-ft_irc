/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_timeout.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:58:38 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/30 16:26:02 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THR_TIMEOUT_HPP
	#define THR_TIMEOUT_HPP

	#include "IRC.hpp"
	#include "Client.hpp"
	#include "connections.hpp"

/* ************************************************************************** */

void	*thr_timeout(void *arg);

/* ************************************************************************** */

#endif
