/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:29:58 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:42:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "utils/utils.hpp"
#include "utils/ircResponses.hpp"
#include "classes/Channel.hpp"

/* ************************************************************************** */

void	Client::PART(string_t content)
{
	string_t			channelToLeave;

	if (content.length() < 2 || content[0] != '#')
		return ;
	else
		content = content.substr(1);
	channelToLeave = rTrim(content);
	transform(channelToLeave.begin(), channelToLeave.end(), channelToLeave.begin(), tolower);
	if (g_channels.find(channelToLeave) != g_channels.end() && this->_channels.find(channelToLeave) != this->_channels.end())
	{
		g_channels[channelToLeave].disconnect(this);
		this->_channels.erase(channelToLeave);
		this->sendMessage(formatIrcMessage(this->getFullname(), "#" + channelToLeave, "PART", content));
	}
}
