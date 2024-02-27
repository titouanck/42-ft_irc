/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:32:20 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/27 23:37:49 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

void	Client::TOPIC(string_t content)
{
	size_t			pos;
	string_t		channelName;
	string_t		channelTopic;
	Channel			*channel;
	
	if (content.length() < 2 || content[0] != '#')
		return ;
	content.erase(0, 1);
	pos = content.find_first_of(" \t");
	channelName = content.substr(0, pos);
	transform(channelName.begin(), channelName.end(), channelName.begin(), tolower);
	if (g_channels.find(channelName) == g_channels.end())
		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " #" + channelName, "No such channel"));
	channel = &(g_channels.find(channelName)->second);
	channelTopic = channel->getTopic();
	if (channel->isConnected(this) == false)
		return sendMessage(formatIrcMessage(g_servername, ERR_NOTONCHANNEL, this->_nickname + " #" + channelName, "You're not on that channel"));
	if (pos == std::string::npos)
	{
		if (channelTopic.empty())
			return sendMessage(formatIrcMessage(g_servername, RPL_NOTOPIC, this->_nickname + " #" + channelName, "No topic is set"));
		sendMessage(formatIrcMessage(g_servername, RPL_TOPIC, this->_nickname + " #" + channelName, channelTopic));
		sendMessage(formatIrcMessage(g_servername, RPL_TOPICWHOTIME, this->_nickname + " #" + channelName + " " + channel->getTopicWhoTime(), ""));
		return ;
	}
	pos = content.find(':');
	if (pos == std::string::npos)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname + " #" + channelName, "TOPIC needs more parameters"));
	content = content.substr(pos + 1);
	if (channel->isTopicRestricted() && channel->isOp(this) == false)
		return sendMessage(formatIrcMessage(g_servername, ERR_CHANOPRIVSNEEDED, this->_nickname + " #" + channelName, "You're not channel operator"));
	channel->setTopic(this, content);
	channel->sendMessage(NULL, formatIrcMessage(this->getFullname(), "TOPIC", "#" + channelName, channel->getTopic()));
}
