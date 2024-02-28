/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:59:35 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/27 23:42:07 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/utils.hpp"
#include "utils/ircNumerics.hpp"

/* ************************************************************************** */

void	Client::INVITE(string_t content)
{
	string_t		channelName;
	string_t		givenNickname;
	size_t			pos;

	if (content.empty())
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "INVITE needs more parameters"));
	
	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, content, "INVITE needs more parameters"));
	
	givenNickname = content.substr(0, pos);
	channelName = trim(content.substr(pos));

	if (channelName[0] != '#' || channelName.length() == 1)
		return sendMessage(formatIrcMessage(g_servername, ERR_BADCHANMASK, content, "Syntax error, invalid channel name"));

	channelName.erase(0, 1);
	transform(channelName.begin(), channelName.end(), channelName.begin(), tolower);
	transform(givenNickname.begin(), givenNickname.end(), givenNickname.begin(), tolower);
	
	std::cout << "channelName:" << channelName << '\n';
	std::cout << "givenNickname:" << givenNickname << '\n';

	if (nicknames.find(givenNickname) == nicknames.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, this->_nickname + " " + givenNickname, "No such nickname"));
	else if (g_channels.find(channelName) == g_channels.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelName, "No such channel"));
	else if (!g_channels[channelName].isConnected(this))
		return sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, this->_nickname + " #" + channelName, "You're not on channel"));
	else if (g_channels[channelName].isConnected(nicknames[givenNickname]))
		return sendMessage(formatIrcMessage(g_servername, ERR_USERONCHANNEL, this->_nickname + " " + givenNickname, "User already on channel"));
	else if (!g_channels[channelName].isOp(this))
		return sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, this->_nickname + " #" + channelName, "You're not channel operator"));

	g_channels[channelName].sendMessage(NULL, formatIrcMessage(this->getFullname(), RPL_INVITING, givenNickname + " #" + channelName, ""));
	g_channels[channelName].invite(nicknames[givenNickname]);
}