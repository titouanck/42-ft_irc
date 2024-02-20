/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:23:55 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:42:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "utils/ircResponses.hpp"

/* ************************************************************************** */

void	Client::NICK(string_t nickname)
{
	bool	sendWelcomeBurst;

	sendWelcomeBurst = false;
	transform(nickname.begin(), nickname.end(), nickname.begin(), tolower);
	if (!this->isAuthenticated())
		return this->sendMessage(formatReference(GUEST, ERR_NOTREGISTERED()));
	else if (this->_nickname.compare(nickname) == 0)
		return ;
	nickname = rTrim(nickname.substr(0, nickname.find(':')));
	if (!checkStrValidity(nickname) || nickname.compare(GUEST) == 0)
		return this->sendMessage(formatReference(GUEST, ERR_ERRONEUSNICKNAME()));
	pthread_mutex_lock(&nicknames_mutex);
	if (nicknames.find(nickname) == nicknames.end())
	{
		if (this->_nickname.length() == 0)
			sendWelcomeBurst = true;
		else
			nicknames.erase(this->_nickname);
		nicknames[nickname] = this;
		this->_nickname = nickname;
		if (sendWelcomeBurst)
		{
			this->sendMessage(welcomeBurst(*this));
			sendWelcomeBurst = false;
		}
	}
	else
		this->sendMessage(formatReference(GUEST, ERR_NICKNAMEINUSE(nickname)));
	pthread_mutex_unlock(&nicknames_mutex);
}
