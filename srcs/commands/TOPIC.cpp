/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:32:20 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 04:49:32 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircResponses.hpp"

/* ************************************************************************** */

void	Client::TOPIC(string_t content)
{
	size_t			pos;
	string_t		givenChannel;
	
	if (content.length() < 2 || content[0] != '#')
		return ;
	else
		content = content.substr(1);
	pos = content.find_first_of(" \t");
	givenChannel = content.substr(0, pos);
	transform(givenChannel.begin(), givenChannel.end(), givenChannel.begin(), tolower);
	if (pos == std::string::npos)
	{
		// if (g_channels.find(givenChannel) != g_channels.end())
		// 	this->sendMessage(formatReference(this->_nickname + " #" + givenChannel, RPL_TOPIC(g_channels[givenChannel])));
		// else
		// 	this->sendMessage(formatReference(this->_nickname + " #" + givenChannel, ERR_NOSUCHCHANNEL()));
		return ;
	}
	// givenChannel = content.substr(0, pos);
	// content = content.substr(pos + 1);
}
