/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:32:20 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 12:09:34 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

// void	_modeParameter(Client *client, Channel &channel, string_t content)
// {
// 	char		operation;
// 	char		modechar;
// 	string_t	remaining;
// 	size_t		pos;

// 	if (content[0] != '+' && content[0] != '-')
// 		return ;
// 	operation = content[0];
// 	content.erase(0, 1);
// 	pos = content.find_first_of("+-");
// 	if (pos != std::string::npos)
// 		remaining = content.substr(pos);
// 	content = content.substr(0, pos);
// 	if (content.empty() || (content.length() >= 2 && (content[1] != ' ' && content[1] != '\t')))
// 		return client->sendMessage(formatIrcMessage(g_servername, "MODE", client->getNickname(), "Syntax error, MODE <channel|nickname> [[+|-]modechars [parameters]]"));
// 	modechar = content[0];
// 	content = trim(content.substr(1));
// 	switch (modechar)
// 	{
// 		case 'i':
// 			if (operation == '-')
// 				channel.setInviteOnly(false);
// 			else
// 				channel.setInviteOnly(true);
// 			break ;
// 		case 't':
// 			if (operation == '-')
// 				channel.setTopicRestricted(false);
// 			else
// 				channel.setTopicRestricted(true);
// 			break ;
// 		case 'k':
// 			if (operation == '-')
// 				channel.setChannelKey("");
// 			else
// 				channel.setChannelKey(content);
// 			break ;
// 		case 'o':
// 			if (operation == '-')
// 			{
// 				if (content.compare(client->getNickname()) == 0)
// 					channel.deop(client);
// 				else
// 					client->sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, client->getNickname() + " #" + channel.getName(), "You're not channel operator"));
// 			}
// 			else
// 			{
// 				if (Client::nicknames.find(content) != Client::nicknames.end() && channel.isConnected(Client::nicknames[content]))
// 					channel.op(Client::nicknames[content]);
// 			}
// 			break ;
// 		case 'l':
// 			if (operation == '-')
// 				channel.setUserLimit(0);
// 			else
// 				channel.setUserLimit(safeStrtoi(content));
// 			break ;
// 	}
// 	if (remaining.length() > 0)
// 		_modeParameter(client, channel, remaining);
// }

// void _printChannelModes(string_t channelName)
// {
// 	if (g_channels.find(channelName) == g_channels.end())
// 		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelName, "No such channel"));
// 	else if (!g_channels[channelName].isConnected(this))
// 		return sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, this->_nickname + " #" + channelName, "You're not on channel"));
// 	sendMessage(formatIrcMessage(g_servername, RPL_CHANNELMODEIS, this->_nickname + " #" + channelName, "+" + g_channels[channelName].getModeList()));
// }

// void _printUserModes(string_t nickname)
// {
// 	if (Client::nicknames.find(givenNickname) == Client::nicknames.end())
// 		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, this->_nickname + " " + givenNickname, "No such nick"));
// 	sendMessage(formatIrcMessage(g_servername, RPL_CHANNELMODEIS, this->_nickname + " " + nickname, "+" + Client::nicknames[givenNickname].getModeList()));
// }

// void	Client::MODE(string_t content)
// {
// 	string_t	name;
// 	bool		isChannel;
// 	size_t		pos;

// 	if (content.empty())
// 		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "MODE needs more parameters"));
	
// 	if (content[0] == '#')
// 	{
// 		name = content.substr(1);
// 		isChannel = true;
// 	}
// 	else
// 	{
// 		name = content;
// 		isChannel = false;
// 	}
	
// 	pos = content.find_first_of(" \t");
// 	name = name.substr(0, pos);
// 	if (name.empty())
// 	{
// 		if (isChannel)
// 			return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #", "Syntax error, no channel name is given"));
// 		else
// 			return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, this->_nickname, "Syntax error, no nickname is given"));
// 	}
// 	if (pos == std::string::npos)
// 	{
// 		if (isChannel)
// 			return _printChannelModes(name);
// 		else
// 			return _printUserModes(names);
// 	}
	// if (g_channels.find(name) == g_channels.end())
	// 	return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + name, "No such channel"));
	// if (pos == std::string::npos)
	// 	return sendMessage(formatIrcMessage(g_servername, RPL_CHANNELMODEIS, this->_nickname + " #" + name + " +" + g_channels[name].getModeList(), ""));
	// if ((content[1] == '+' || content[1] == '-') && !g_channels[name].isOp(this))
	// 	return sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, this->_nickname + " #" + name, "You're not channel operator"));
	// _modeParameter(this, g_channels[name], content.substr(pos + 1));
// }


void	Client::MODE(string_t content)
{
	(void)	content;
// 	string_t	name;
// 	size_t		pos;

// 	if (content.length() >= 1 && content[0] == '#')
// 		content.erase(0, 1);
// 	else if (content.empty() || content[0] == '#')
// 		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "MODE needs more parameters"));
// 	else
// 		return ;
// 	pos = content.find_first_of(" \t");
// 	name = content.substr(0, pos);
// 	if (g_channels.find(name) == g_channels.end())
// 		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + name, "No such channel"));
// 	if (pos == std::string::npos)
// 		return sendMessage(formatIrcMessage(g_servername, RPL_CHANNELMODEIS, this->_nickname + " #" + name + " +" + g_channels[name].getModeList(), ""));
// 	if ((content[1] == '+' || content[1] == '-') && !g_channels[name].isOp(this))
// 		return sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, this->_nickname + " #" + name, "You're not channel operator"));
// 	_modeParameter(this, g_channels[name], content.substr(pos + 1));
}
