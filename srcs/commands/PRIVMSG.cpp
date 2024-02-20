/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:33:04 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:42:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircResponses.hpp"

/* ************************************************************************** */

void	Client::PRIVMSG(string_t content)
{
	bool				isChannelName;
	string_t			receiver;
	size_t				pos;

	if (content.length() > 2 && content[0] == '#')
		isChannelName = true;
	else
		isChannelName = false;
	pos = content.find(':');
	if (pos == std::string::npos)
		return ;
	receiver = rTrim(content.substr(0, pos));
	transform(receiver.begin(), receiver.end(), receiver.begin(), tolower);
	content = content.substr(pos + 1);
	
	if (!isChannelName)
	{
		if (receiver.compare(this->_nickname) == 0)
			return ;
		if (nicknames.find(receiver) != nicknames.end())
			nicknames[receiver]->sendMessage(formatIrcMessage(this->getFullname(), receiver, "PRIVMSG", content));
		else
			this->sendMessage(formatReference(this->_nickname + " " + receiver, ERR_NOSUCHNICK()));
	}
	else if (isChannelName)
	{
		if (g_channels.find(receiver.substr(1)) != g_channels.end())
		{
			if (g_channels[receiver.substr(1)].isConnected(this))
				g_channels[receiver.substr(1)].sendMessage(this, formatIrcMessage(this->getFullname(), receiver, "PRIVMSG", content));
			else
				this->sendMessage(formatReference(this->_nickname + " " + receiver, ERR_CANNOTSENDTOCHAN()));
		}
		else
			this->sendMessage(formatReference(this->_nickname + " " + receiver, ERR_NOSUCHCHANNEL()));
	}
}
