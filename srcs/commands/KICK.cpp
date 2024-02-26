/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:30:58 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 18:29:37 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"
#include "utils/ircNumerics.hpp"
#include "classes/Client.hpp"
#include "classes/Channel.hpp"

/* ************************************************************************** */

void	Client::KICK(string_t content)
{
	string_t		channelName;
	string_t		givenNickname;
	size_t			pos;

	if (content.length() == 0)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "KICK needs more parameters"));
	else if (content[0] != '#' || content.length() == 1)
		return sendMessage(formatIrcMessage(g_servername, ERR_BADCHANMASK, this->_nickname + " " + content, "Invalid channel name"));
	
	content = content.substr(1);
	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname + " #" + channelName, "KICK needs more parameters"));
	channelName = content.substr(0, pos);
	
	if (!containsOnlyAllowedChars(channelName))
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelName, "Channel name contains invalid characters"));
	
	content = content.substr(pos + 1);
	pos = content.find(':');
	givenNickname = rTrim(content.substr(0, pos));
	
	if (givenNickname.length() == 0)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname + " #" + channelName, "KICK needs more parameters"));
	
	if (pos != std::string::npos)
		content = content.substr(pos + 1);
	else
		content = "";

	transform(channelName.begin(), channelName.end(), channelName.begin(), tolower);
	transform(givenNickname.begin(), givenNickname.end(), givenNickname.begin(), tolower);
	
	if (g_channels.find(channelName) == g_channels.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelName, "No such channel"));
	else if (nicknames.find(givenNickname) == nicknames.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, this->_nickname + " " + givenNickname, "No such nickname"));
	else if (!g_channels[channelName].isConnected(this))
		return sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, this->_nickname + " #" + channelName, "Not on channel"));
	else if (!g_channels[channelName].isOp(this))
		return sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, this->_nickname + " #" + channelName, "You're not channel operator"));
	else if (g_channels[channelName].isOp(nicknames[givenNickname]))
		return sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, this->_nickname + " #" + channelName, "Not enough permissions"));
	
	g_channels[channelName].sendMessage(NULL, formatIrcMessage(this->getFullname(), "KICK", "#" + channelName + " " + givenNickname, content));
	nicknames[givenNickname]->_channels.erase(channelName);
	g_channels[channelName].disconnect(nicknames[givenNickname]);
}
