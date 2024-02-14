/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_timeout.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:59:13 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/14 01:32:31 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thr_timeout.hpp"
#include "numericReferences.hpp"

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
					clients[i].disconnect();
				}
				else if (clients[i].isPinged() == false && clients[i].getPingTime() + (TIMEOUTSEC * 2) < std::time(0))
				{
					switch (std::time(0) % 2)
					{
						case 0:
							clients[i].setPingContent(g_servername);
							clients[i].sendMessage("PING :" + g_servername + "\n");
							break ;
						default:
							clients[i].setPingContent(g_serversion);
							clients[i].sendMessage("PING :" + g_serversion + "\n");
							break ;
					}
				}
			}
			clients[i].unlockMutex();
		}
		pthread_mutex_lock(&g_endOfProgram_mutex);
		if (g_endOfProgram)
			break ;
		pthread_mutex_unlock(&g_endOfProgram_mutex);
	}
	pthread_mutex_unlock(&g_endOfProgram_mutex);
	pthread_exit(NULL);
}

/* ************************************************************************** */
