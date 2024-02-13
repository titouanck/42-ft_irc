/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_timeout.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:59:13 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/13 02:29:46 by tchevrie         ###   ########.fr       */
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
				{
					std::cout << "TIMEOUT" << '\n';
					removeConn(clients[i]);
				}
			}
			clients[i].unlockMutex();
		}
		pthread_mutex_lock(&endOfProgram_mutex);
		if (endOfProgram)
			break ;
		pthread_mutex_unlock(&endOfProgram_mutex);
	}
	pthread_mutex_unlock(&endOfProgram_mutex);
	pthread_exit(NULL);
}

/* ************************************************************************** */
