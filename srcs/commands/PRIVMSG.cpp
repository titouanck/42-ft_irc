/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:33:04 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/27 17:07:44 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */


void parsingReceiver(string_t content, string_t msg, Client &client)
{
	size_t		pos;
	bool		isChannelName;
	string_t 	name;
	
	content = trim(content);
	if (content[0] == '#')
	{
		content = content.substr(1);
		isChannelName = true;
	}
	else
		isChannelName = false;
	
	pos = content.find("@");
	name = content;
	if (pos != std::string::npos)
	{
		if (content.substr(pos+1) != client.getIp() && content.substr(pos+1) != client.getName())
			std::cout << "MESSAGE ERRUR \n";
		name = content.substr(pos-1);
	}
	transform(name.begin(), name.end(), name.begin(), tolower);
	std::cout << "name: " << name << "\n";
	if (!isChannelName)
	{
		if (client.nicknames.find(name) == client.nicknames.end())
			return client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, client.getNickname() + " " + name, "No such nickname"));
		else
			client.nicknames[name]->sendMessage(formatIrcMessage(client.getFullname(), "PRIVMSG", name, msg));
	}
	else if (isChannelName)
	{
		if (g_channels.find(name.substr(1)) != g_channels.end())
		{
			if (g_channels[name.substr(1)].isConnected(&client))
				g_channels[name.substr(1)].sendMessage(&client, formatIrcMessage(client.getFullname(), "PRIVMSG", name, content));
			else
				client.sendMessage(formatIrcMessage(g_servername, ERR_CANNOTSENDTOCHAN, client.getNickname() + " " + name, "Cannot send to channel"));
		}
		else
			client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, client.getNickname() + " " + name, "No such channel"));
	}
}


void	Client::PRIVMSG(string_t content)
{
	string_t	name;
	size_t		pos;
	string_t	msg;

	if (content.length() <= 2)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "PRIVMSG needs more parameters"));	
	pos = content.find(':');
	if (pos == std::string::npos)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "PRIVMSG needs more parameters"));	
	msg = content.substr(pos + 1);
	content = content.substr(pos - 1);
	for (int i = 0; i < 2; i++)
	{
		pos = content.find(',');
		if (pos == std::string::npos)
		{
			parsingReceiver(content, msg, *this);
			break ;
		}
		parsingReceiver(content.substr(0, pos), msg, *this);
		content = content.substr(pos+1);
		

	}
	

	
	// if (!isChannelName)
	// {
	// 	if (nicknames.find(name) == nicknames.end())
	// 		return sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, this->_nickname + " " + name, "No such nickname"));
	// 	else
	// 		nicknames[name]->sendMessage(formatIrcMessage(this->getFullname(), "PRIVMSG", name, content));
	// }
	// else if (isChannelName)
	// {
	// 	if (g_channels.find(name.substr(1)) != g_channels.end())
	// 	{
	// 		if (g_channels[name.substr(1)].isConnected(this))
	// 			g_channels[name.substr(1)].sendMessage(this, formatIrcMessage(this->getFullname(), "PRIVMSG", name, content));
	// 		else
	// 			sendMessage(formatIrcMessage(g_servername, ERR_CANNOTSENDTOCHAN, this->_nickname + " " + name, "Cannot send to channel"));
	// 	}
	// 	else
	// 		sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, this->_nickname + " " + name, "No such channel"));
	// }
}
