/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:32:20 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 00:53:26 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

static void	_modeParameter(Client *client, Channel &channel, string_t content)
{
	char		operation;
	char		modechar;
	string_t	remaining;
	size_t		pos;

	if (content[0] != '+' && content[0] != '-')
		return ;
	operation = content[0];
	content = content.substr(1);
	pos = content.find_first_of("+-");
	if (pos != std::string::npos)
		remaining = content.substr(pos);
	content = content.substr(0, pos);
	if (content.length() == 0 || (content.length() >= 2 && (content[1] != ' ' && content[1] != '\t')))
		return client->sendMessage(formatIrcMessage(g_servername, "MODE", client->getNickname(), "Syntax error, MODE <channel|nickname> [[+|-]modechars [parameters]]"));
	modechar = content[0];
	content = trim(content.substr(1));
	switch (modechar)
	{
		case 'i':
			if (operation == '-')
				channel.setInviteOnly(false);
			else
				channel.setInviteOnly(true);
			break ;
		case 't':
			if (operation == '-')
				channel.setTopicRestricted(false);
			else
				channel.setTopicRestricted(true);
			break ;
		case 'k':
			if (operation == '-')
				channel.setChannelKey("");
			else
				channel.setChannelKey(content);
			break ;
		case 'o':
			if (operation == '-')
			{
				if (content.compare(client->getNickname()) == 0)
					channel.deop(client);
				else
					client->sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, client->getNickname() + " #" + channel.getName(), "You're not channel operator"));
			}
			else
			{
				if (Client::nicknames.find(content) != Client::nicknames.end() && channel.isConnected(Client::nicknames[content]))
					channel.op(Client::nicknames[content]);
			}
			break ;
		case 'l':
			if (operation == '-')
				channel.setUserLimit(0);
			else
				channel.setUserLimit(safeStrtoi(content));
			break ;
	}
	if (remaining.length() > 0)
		_modeParameter(client, channel, remaining);
}

void	Client::MODE(string_t content)
{
	string_t	name;
	size_t		pos;

	if (content.length() >= 1 && content[0] == '#')
		content = content.substr(1);
	else if (content.length() == 0 || content[0] == '#')
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "Need more parameters, MODE <channel|nickname> [[+|-]modechars [parameters]]"));
	else
		return ;
	pos = content.find_first_of(" \t");
	name = content.substr(0, pos);
	if (g_channels.find(name) == g_channels.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + name, "No such channel"));
	if (pos == std::string::npos)
		return sendMessage(formatIrcMessage(g_servername, RPL_CHANNELMODEIS, this->_nickname + " #" + name + " +" + g_channels[name].getModeList(), ""));
	if ((content[1] == '+' || content[1] == '-') && !g_channels[name].isOp(this))
		return sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, this->_nickname + " #" + name, "You're not channel operator"));
	_modeParameter(this, g_channels[name], content.substr(pos + 1));
}
