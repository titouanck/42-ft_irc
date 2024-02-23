/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:33:04 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/24 00:07:53 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

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
			nicknames[receiver]->sendMessage(formatIrcMessage(this->getFullname(), "PRIVMSG", receiver, content));
		else
			sendMessage(formatIrcMessage(g_servername, 401, this->_nickname + " " + receiver, "No such nickname"));
	}
	else if (isChannelName)
	{
		if (g_channels.find(receiver.substr(1)) != g_channels.end())
		{
			if (g_channels[receiver.substr(1)].isConnected(this))
				g_channels[receiver.substr(1)].sendMessage(this, formatIrcMessage(this->getFullname(), "PRIVMSG", receiver, content));
			else
				sendMessage(formatIrcMessage(g_servername, ERR_CANNOTSENDTOCHAN, this->_nickname + " " + receiver, "Cannot send to channel"));
		}
		else
			sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " " + receiver, "No such channel"));
	}
}
