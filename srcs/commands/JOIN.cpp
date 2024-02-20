/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:28:03 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 04:50:28 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/utils.hpp"
#include "utils/ircNumerics.hpp"

/* ************************************************************************** */

void	Client::JOIN(string_t content)
{
	std::stringstream	oss;
	string_t			remaining;
	string_t			channelKey;
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
	oss << formatIrcMessage(this->getFullname(), "JOIN", "#" + content, "");
	if (g_channels.find(content) == g_channels.end())	/* If channel doesn't exist */
	{
		g_channels[content] = Channel();
		g_channels[content].setName(content);
		oss << formatIrcMessage(g_servername, RPL_NAMREPLY, this->_nickname + " = #" + content, "@" + this->_nickname);
		isOp = true;
	}
	else 												/* If channel does exist */
	{
		oss << formatIrcMessage(g_servername, RPL_NAMREPLY, this->_nickname + " = #" + content, this->_nickname + " " + g_channels[content].getUserList());
		isOp = false;
	}
	oss << formatIrcMessage(g_servername, RPL_ENDOFNAMES, this->_nickname + " #" + content, "End of /NAMES list");
	
	if (this->_channels.find(content) == this->_channels.end())
	{
		this->sendMessage(oss.str());
		this->_channels.insert(content);
		g_channels[content].connect(this);
		if (isOp)
			g_channels[content].op(this);
	}
	this->JOIN(lTrim(remaining));
}
