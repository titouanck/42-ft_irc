/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_timeout.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:59:13 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/25 18:12:14 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thr_timeout.hpp"

/* ************************************************************************** */

void	*thr_timeout(void *arg)
{
	Client	*clients = (static_cast<Client (*)>(arg));

	while (true)
	{
		for (int i = 0; i <= MAX_CLIENTS; i++)
		{
			clients[i].lockMutex();
			if (clients[i].getIdentity().length() != 0)
			{
				if (clients[i].isPinged() == true && clients[i].getPingTime() + TIMEOUTSEC < std::time(0))
					removeConn(clients[i]);
			}
			clients[i].unlockMutex();
		}
	}
	pthread_exit(NULL);
}

/* ************************************************************************** */
