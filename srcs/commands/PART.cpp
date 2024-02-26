/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:29:58 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 19:11:19 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "utils/utils.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"

/* ************************************************************************** */

void	Client::PART(string_t content)
{
	string_t			channelToLeave;

	if (content.length() == 0)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "PART needs more parameters"));
	else if (content[0] != '#' || content.length() == 1)
		return sendMessage(formatIrcMessage(g_servername, ERR_BADCHANMASK, this->_nickname + " " + content, "Invalid channel name"));

	content = content.substr(1);
	channelToLeave = rTrim(content);
	transform(channelToLeave.begin(), channelToLeave.end(), channelToLeave.begin(), tolower);
	
	if (!containsOnlyAllowedChars(channelToLeave))
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelToLeave, "Channel name contains invalid characters"));
	
	if (g_channels.find(channelToLeave) == g_channels.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelToLeave, "No such channel"));
	else if (!g_channels[channelToLeave].isConnected(this) || this->_channels.find(channelToLeave) == this->_channels.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, this->_nickname + " #" + channelToLeave, "You're not on channel"));

	g_channels[channelToLeave].disconnect(this);
	g_channels[channelToLeave].sendMessage(NULL, formatIrcMessage(this->getFullname(), "PART", "#" + channelToLeave, content));
	this->_channels.erase(channelToLeave);
	sendMessage(formatIrcMessage(this->getFullname(), "PART", "#" + channelToLeave, content));
}
