/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:18:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:40:39 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Server.hpp"

/* ************************************************************************** */

void	Client::PASS(string_t passphrase)
{
	if (this->_authenticated || passphrase.compare(Server::getPassword()) != 0)
		this->disconnect();
	else
	{
		this->_authenticated = true;
		this->_pinged = false;
	}
}
