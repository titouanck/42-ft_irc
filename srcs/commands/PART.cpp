/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:29:58 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 19:32:02 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "utils/utils.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"

/* ************************************************************************** */

void	Client::PART(string_t content)
{
	string_t	channelToLeave;
	string_t	remaining;
	size_t		pos;

	if (content.length() == 0)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "PART needs more parameters"));
	else if (content[0] != '#' || content.length() == 1)
		return sendMessage(formatIrcMessage(g_servername, ERR_BADCHANMASK, this->_nickname + " " + content, "Invalid channel name"));

	pos = content.find(',');
	if (pos != std::string::npos)
		remaining = lTrim(content.substr(pos + 1));
	channelToLeave = rTrim(content.substr(1, pos - 1));
	transform(channelToLeave.begin(), channelToLeave.end(), channelToLeave.begin(), tolower);
	
	if (!containsOnlyAllowedChars(channelToLeave))
		sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelToLeave, "Channel name contains invalid characters"));
	else if (g_channels.find(channelToLeave) == g_channels.end())
		sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelToLeave, "No such channel"));
	else if (!g_channels[channelToLeave].isConnected(this) || this->_channels.find(channelToLeave) == this->_channels.end())
		sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, this->_nickname + " #" + channelToLeave, "You're not on channel"));
	else
	{
		g_channels[channelToLeave].disconnect(this);
		g_channels[channelToLeave].sendMessage(NULL, formatIrcMessage(this->getFullname(), "PART", "#" + channelToLeave, channelToLeave));
		this->_channels.erase(channelToLeave);
		sendMessage(formatIrcMessage(this->getFullname(), "PART", "#" + channelToLeave, channelToLeave));
	}
	
	if (remaining.length() > 0)
		this->PART(remaining);
}
