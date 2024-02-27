/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:18:52 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/27 18:54:37 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Server.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

void	Client::PASS(string_t passphrase)
{
	if (this->_authenticated)
		return sendMessage(formatIrcMessage(g_servername, "NOTICE", this->_nickname, "You have already authenticated"));
	if (passphrase.compare(Server::getPassword()) != 0)
	{
		std::cout << "----------------------------------------" << '\n';
		sendMessage(formatIrcMessage(g_servername, ERR_PASSWDMISMATCH, this->_nickname, "Passwords don't match"));
		this->disconnect();
		return ;
	}
	this->_authenticated = true;
	this->_pinged = false;
}
