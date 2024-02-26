/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:28:03 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 18:46:35 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/utils.hpp"
#include "utils/ircNumerics.hpp"

#define MAX_CHANNELS_PER_USER 10

/* ************************************************************************** */

static string_t	joinBurst(Client &client, Channel &channel, string_t userList)
{
	string_t	str;
	string_t	nickname;
	string_t	channelName;
	string_t	modeList;
	string_t	channelTopic;

	nickname = client.getNickname();
	channelName = channel.getName();
	channelTopic = channel.getTopic();
	modeList = channel.getModeList();
	channel.sendMessage(NULL, formatIrcMessage(client.getFullname(), "JOIN", "#" + channelName, ""));
	str += formatIrcMessage(client.getFullname(), "JOIN", "#" + channelName, "");
	if (modeList.length() > 0)
		str += formatIrcMessage(g_servername, "MODE", nickname + " #" + channelName + " +" + modeList, "");
	if (channelTopic.length() > 0)
	{
		str += formatIrcMessage(g_servername, RPL_TOPIC, nickname + " #" + channelName, channelTopic);
		str += formatIrcMessage(g_servername, RPL_TOPICWHOTIME, nickname + " #" + channelName + " " + channel.getTopicWhoTime(), "");
	}
	if (userList.length() == 0)
		str += formatIrcMessage(g_servername, RPL_NAMREPLY, nickname + " = #" + channelName, "@" + nickname);
	else
		str += formatIrcMessage(g_servername, RPL_NAMREPLY, nickname + " = #" + channelName, nickname + " " + userList);
	str += formatIrcMessage(g_servername, RPL_ENDOFNAMES, nickname + " #" + channelName, "End of /NAMES list");
	return str;
}

static string_t	_parsing(string_t content, string_t &channelName, string_t &channelKey)
{
	string_t	remaining;
	size_t		pos;

	pos = content.find(',');
	if (pos != std::string::npos)
		remaining = content.substr(pos + 1);
	content = content.substr(0, pos);
	pos = content.find_first_of(" \t");
	if (pos != std::string::npos)
		channelKey = content.substr(pos + 1);
	channelName = content.substr(0, pos);
	transform(channelName.begin(), channelName.end(), channelName.begin(), tolower);
	return remaining;
}

void	Client::JOIN(string_t content)
{
	string_t	channelName;
	string_t	channelKey;
	string_t	remaining;
	string_t	userList;
	bool		isOp;

	if (content.length() == 0)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "JOIN needs more parameters"));
	else if (content[0] != '#' || content.length() == 1)
		return sendMessage(formatIrcMessage(g_servername, ERR_BADCHANMASK, this->_nickname + " " + content, "Invalid channel name"));
	remaining = _parsing(content.substr(1), channelName, channelKey);
	if (this->_channels.size() >= MAX_CHANNELS_PER_USER)
		return sendMessage(formatIrcMessage(g_servername, ERR_TOOMANYCHANNELS, this->_nickname + " " + channelName, "Too many channels"));
	else if (!containsOnlyAllowedChars(channelName))
	{
		sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelName, "Channel name contains invalid characters"));
		if (remaining.length() > 0)
			this->JOIN(lTrim(remaining));
		return ;
	}
	else if (g_channels.find(channelName) == g_channels.end())
	{
		g_channels[channelName] = Channel();
		g_channels[channelName].setName(channelName);
		isOp = true;
	}
	else
	{
		userList = g_channels[channelName].getUserList();
		isOp = false;
	}
	if (this->_channels.find(channelName) == this->_channels.end())
	{
		switch (g_channels[channelName].checkEligibilityToConnect(this, channelKey))
		{
			case ERR_CHANNELISFULL:
				sendMessage(formatIrcMessage(g_servername, ERR_CHANNELISFULL, this->_nickname + " #" + channelName, "Cannot join channel (+l)"));
				break ;
			case ERR_INVITEONLYCHAN:
				sendMessage(formatIrcMessage(g_servername, ERR_INVITEONLYCHAN, this->_nickname + " #" + channelName, "Cannot join channel (+i)"));
				break ;
			case ERR_BADCHANNELKEY:
				sendMessage(formatIrcMessage(g_servername, ERR_BADCHANNELKEY, this->_nickname + " #" + channelName, "Cannot join channel (+k) - bad key"));
				break ;
			default:
				std::cout << "ICI LA" << '\n';
				sendMessage(joinBurst(*this, g_channels[channelName], userList));
				this->_channels.insert(channelName);
				g_channels[channelName].connect(this);
				if (isOp)
					g_channels[channelName].op(this);
		}
	}
	if (remaining.length() > 0)
		this->JOIN(lTrim(remaining));
}
