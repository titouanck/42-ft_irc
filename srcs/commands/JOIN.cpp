/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:28:03 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:42:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"
#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircResponses.hpp"

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
	oss << ":" << this->_nickname;
	if (this->_username.length() > 0)
		oss << "!" << this->_username;
	oss << "@" << g_servername << " JOIN #" << content << '\n';
	if (g_channels.find(content) == g_channels.end())	/* If channel doesn't exist */
	{
		g_channels[content] = Channel();
		g_channels[content].setName(content);
		oss << formatReference(this->_nickname + " = #" + content, (IrcResponse){"353", "@" + this->_nickname});
		isOp = true;
	}
	else 												/* If channel does exist */
	{
		oss << formatReference(this->_nickname + " = #" + content, RPL_NAMREPLY(this->_nickname, g_channels[content].getUsers()));
		isOp = false;
	}
	
	if (this->_channels.find(content) == this->_channels.end())
	{
		oss << formatReference(this->_nickname + " #" + content, (IrcResponse){"366", "End of /NAMES list"});
		this->sendMessage(oss.str());
		this->_channels.insert(content);
		g_channels[content].connect(this);
		if (isOp)
			g_channels[content].op(this);
	}
	this->JOIN(lTrim(remaining));
}
