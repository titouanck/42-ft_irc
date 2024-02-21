/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:28:03 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/21 14:07:46 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/utils.hpp"
#include "utils/ircNumerics.hpp"

/* ************************************************************************** */

static string_t	joinBurst(Client &client, Channel &channel, string_t userList)
{
	string_t	str;
	string_t	nickname;
	string_t	channelName;
	string_t	channelTopic;

	nickname = client.getNickname();
	channelName = channel.getName();
	channelTopic = channel.getTopic();
	str += formatIrcMessage(client.getFullname(), "JOIN", "#" + channelName, "");
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

void	Client::JOIN(string_t content)
{
	string_t			remaining;
	string_t			channelKey;
	string_t			userList;
	size_t				pos;
	bool				isOp;

	if (content.length() < 2 || content[0] != '#')
		return ;
	content = content.substr(1);
	pos = content.find(',');
	if (pos != std::string::npos)
		remaining = content.substr(pos + 1);
	content = content.substr(0, pos);
	pos = content.find_first_of(" \t");
	if (pos != std::string::npos)
		channelKey = content.substr(pos + 1);
	content = content.substr(0, pos);
	if (!checkStrValidity(content))
		return ;
	transform(content.begin(), content.end(), content.begin(), tolower);
	if (g_channels.find(content) == g_channels.end())	/* If channel doesn't exist */
	{
		g_channels[content] = Channel();
		g_channels[content].setName(content);
		isOp = true;
	}
	else 												/* If channel does exist */
	{
		userList = g_channels[content].getUserList();
		isOp = false;
	}
	if (this->_channels.find(content) == this->_channels.end())
	{
		this->sendMessage(joinBurst(*this, g_channels[content], userList));
		this->_channels.insert(content);
		g_channels[content].connect(this);
		if (isOp)
			g_channels[content].op(this);
	}
	this->JOIN(lTrim(remaining));
}
