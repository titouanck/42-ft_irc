/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:33:04 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/27 19:12:23 by ngriveau         ###   ########.fr       */
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
	if (content.empty())
		return ;
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
		
		name = content.substr(0, pos);
		// pos = client.nicknames.find(name);
		// if( != std::string::npos)
		if (content.substr(pos+1) != client.getIp() && content.substr(pos+1) != client.getName())
		{
			std::cout << client.getIp() << "|/| " << client.getName() << std::endl;
			return ;
		}
	}
	transform(name.begin(), name.end(), name.begin(), tolower);
	std::cout << "name: |" << name << "|" << isChannelName << "\n";
	if (!isChannelName)
	{
		if (client.nicknames.find(name) == client.nicknames.end())
			return client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, client.getNickname() + " " + name, "No such nickname"));
		else
			client.nicknames[name]->sendMessage(formatIrcMessage(client.getFullname(), "PRIVMSG", name, msg));
	}
	else if (isChannelName)
	{
		std::cout << "isChannelName OUI\n";
		if (g_channels.find(name) != g_channels.end())
		{
			std::cout << "g_channels.find(name) != g_channels.end()\n";
			
			if (g_channels[name].isConnected(&client))
			{
				std::cout << "g_channels[name].isConnected(&client)\n";
				g_channels[name].sendMessage(&client, formatIrcMessage(client.getFullname(), "PRIVMSG", "#" + name, msg));
			}
			else
				client.sendMessage(formatIrcMessage(g_servername, ERR_CANNOTSENDTOCHAN, client.getNickname() + " #" + name, "Cannot send to channel"));
		}
		else
			client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, client.getNickname() + " #" + name, "No such channel"));
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
	content = content.substr(0, pos - 1);
	std::cout << "ICIIII msg: |" << msg << "| content: |" << content << "|\n";
	while (true)
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

