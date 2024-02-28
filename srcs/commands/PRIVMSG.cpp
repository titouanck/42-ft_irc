/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:33:04 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/28 12:00:35 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

bool checkIsGroup(string_t &content)
{
	if (content[0] != '#')
		return false;
	content = content.substr(1);
	return true;
}

bool checkIsAddress(string_t &content, Client &client)
{
	size_t		pos;

	pos = content.find("@");
	if (pos != std::string::npos)
	{
		string_t name = content.substr(0, pos);
		if (client.nicknames.find(name) == client.nicknames.end() || (content.substr(pos+1) != client.nicknames[name]->getIdentity()))
		{
			client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, client.getNickname() + " " + content, "No such nickname"));
			return false;
		}
		content = name;
	}
	return true;
}


void sendUser(string_t name, string_t msg, Client &client)
{
	if (client.nicknames.find(name) == client.nicknames.end())
		return client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHNICK, client.getNickname() + " " + name, "No such nickname"));
	else
		client.nicknames[name]->sendMessage(formatIrcMessage(client.getFullname(), "PRIVMSG", name, msg));
}

void sendGroup(string_t name, string_t msg, Client &client)
{
	std::cout << "10\n";
	if (g_channels.find(name) != g_channels.end())
	{
		std::cout << "11\n";
		if (g_channels[name].isConnected(&client))
		{
			std::cout << "13\n";
			g_channels[name].sendMessage(&client, formatIrcMessage(client.getFullname(), "PRIVMSG", "#" + name, msg));
		}
		else
		{
			std::cout << "15\n";
			client.sendMessage(formatIrcMessage(g_servername, ERR_CANNOTSENDTOCHAN, client.getNickname() + " #" + name, "Cannot send to channel"));
		}
	}
	else
	{
		std::cout << "12\n";
		client.sendMessage(formatIrcMessage(g_servername, ERR_NOSUCHCHANNEL, client.getNickname() + " #" + name, "No such channel"));
	}
}

void parsingReceiver(string_t content, string_t msg, Client &client)
{
	bool		isChannelName;
	
	content = trim(content);
	std::cout << "8\n";
	if (content.empty())
		return ;
	isChannelName = checkIsGroup(content);
	std::cout << "9\n";
	if(!checkIsAddress(content, client))
		return ;
	std::cout << "10\n";
	transform(content.begin(), content.end(), content.begin(), tolower);
	isChannelName ? sendGroup(content, msg, client) : sendUser(content, msg, client);
}

void	Client::PRIVMSG(string_t content)
{
	string_t	name;
	size_t		pos;
	string_t	msg;
	std::cout << "Start: " << content << "\n";
	if (content.length() <= 2)
		return sendMessage(formatIrcMessage(g_servername, ERR_NEEDMOREPARAMS, this->_nickname, "PRIVMSG needs more parameters"));	
	std::cout << "1\n";
	if (trim(content)[0] == ':')
		return sendMessage(formatIrcMessage(g_servername, ERR_NORECIPIENT, this->_nickname, "PRIVMSG needs a destinatair"));	
	std::cout << "2\n";
	pos = content.find(':');
	if (pos == std::string::npos)
		return sendMessage(formatIrcMessage(g_servername, ERR_NOTEXTTOSEND, this->_nickname, "PRIVMSG needs a messages"));	
	std::cout << "3\n";
	msg = content.substr(pos + 1);
	content = content.substr(0, pos - 1);
	std::cout << "4\n";
	while (true)
	{
		std::cout << "5\n";
			pos = content.find(',');
		if (pos == std::string::npos)
		{
			std::cout << "7\n";
			parsingReceiver(content, msg, *this);
			break ;
		}
		std::cout << "6\n";
		parsingReceiver(content.substr(0, pos), msg, *this);
		content = content.substr(pos+1);
	}
}



// ERR_NORECIPIENT			--
// ERR_NOTEXTTOSEND			--
// ERR_CANNOTSENDTOCHAN   	--
// ERR_NOTOPLEVEL			KO
// ERR_WILDTOPLEVEL			KO
// ERR_TOOMANYTARGETS		KO
// ERR_NOSUCHNICK			--
// RPL_AWAY					KO/Pas utile