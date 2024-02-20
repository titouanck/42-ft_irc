/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:30:58 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:42:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"
#include "utils/ircResponses.hpp"
#include "classes/Client.hpp"
#include "classes/Channel.hpp"

/* ************************************************************************** */

void	Client::KICK(string_t content)
{
	string_t		givenChannel;
	string_t		givenNickname;
	size_t			pos;

	if (content.length() < 2 || content[0] != '#')
		return ;
	else
		content = content.substr(1);
	
	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return ;
	givenChannel = content.substr(0, pos);
	content = content.substr(pos + 1);

	pos = content.find(':');
	givenNickname = rTrim(content.substr(0, pos));
	if (givenNickname.length() == 0)
		return ;
	if (pos != std::string::npos)
		content = content.substr(pos + 1);
	else
		content = "";

	transform(givenChannel.begin(), givenChannel.end(), givenChannel.begin(), tolower);
	transform(givenNickname.begin(), givenNickname.end(), givenNickname.begin(), tolower);
	
	if (g_channels.find(givenChannel) != g_channels.end() && g_channels[givenChannel].isOp(this) && nicknames.find(givenNickname) != nicknames.end() && !g_channels[givenChannel].isOp(nicknames[givenNickname]))
	{
		nicknames[givenNickname]->_channels.erase(givenChannel);
		g_channels[givenChannel].disconnect(nicknames[givenNickname]);
		nicknames[givenNickname]->sendMessage(formatIrcMessage(this->getFullname(), "#" + givenChannel + " " + givenNickname, "KICK", content));
	}
}
