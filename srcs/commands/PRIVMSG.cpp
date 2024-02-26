/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:33:04 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 19:38:49 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

void	Client::PRIVMSG(string_t content)
{
	bool		isChannelName;
	string_t	name;
	size_t		pos;

	if (content.length() <= 2)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "PRIVMSG needs more parameters"));	

	if (content[0] == '#')
	{
		content = content.substr(1);
		isChannelName = true;
	}
	else
		isChannelName = false;
	pos = content.find(':');
	if (pos == std::string::npos)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "PRIVMSG needs more parameters"));	
	name = rTrim(content.substr(0, pos));
	transform(name.begin(), name.end(), name.begin(), tolower);
	content = content.substr(pos + 1);
	
	if (!isChannelName)
	{
		if (nicknames.find(name) == nicknames.end())
			return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, this->_nickname + " " + name, "No such nickname"));
		else
			nicknames[name]->sendMessage(formatIrcMessage(this->getFullname(), "PRIVMSG", name, content));
	}
	else if (isChannelName)
	{
		if (g_channels.find(name.substr(1)) != g_channels.end())
		{
			if (g_channels[name.substr(1)].isConnected(this))
				g_channels[name.substr(1)].sendMessage(this, formatIrcMessage(this->getFullname(), "PRIVMSG", name, content));
			else
				sendMessage(formatIrcMessage(g_servername, ERR_CANNOTSENDTOCHAN, this->_nickname + " " + name, "Cannot send to channel"));
		}
		else
			sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " " + name, "No such channel"));
	}
}
