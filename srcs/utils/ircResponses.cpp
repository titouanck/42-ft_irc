/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircResponses.cpp         	                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:38:12 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/19 23:25:45 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/ircResponses.hpp"
#include "classes/Server.hpp"
#include "classes/Client.hpp"
#include "classes/Channel.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

string_t	formatReference(string_t nickname, IrcResponse ref)
{
	std::ostringstream	oss;
	
	oss << ":" << g_servername << " " << ref.numeric << " " << nickname << " :" << ref.content << '\n';
	return oss.str();
}

/* GROUPS ******************************************************************* */

string_t	welcomeBurst(Client &client)
{
	string_t	str;
	string_t	nickname;

	nickname = client.getNickname();
	str += formatIrcMessage(g_servername, RPL_WELCOME, nickname, "Welcome to the " + g_servername + " Network, " + nickname);
	str += formatIrcMessage(g_servername, RPL_YOURHOST, nickname, "Your host is " + g_servername + ", running version " + g_serversion);
	str += formatIrcMessage(g_servername, RPL_CREATED, nickname, "This server was created " + formatTime(Server::launchTime));
	str += formatIrcMessage(g_servername, RPL_MYINFO, nickname, "-");
	str += formatIrcMessage(g_servername, RPL_MOTDSTART,nickname, "You are in a maze of twisty passages, all alike.");
	str += formatIrcMessage(g_servername, RPL_MOTD, nickname, "-");
	str += formatIrcMessage(g_servername, RPL_ENDOFMOTD, nickname, ">");
	return str;
}

/* REFERENCES *************************************************************** */

// 401
IrcResponse	ERR_NOSUCHNICK()
{
	return (IrcResponse){"401", "No such nickname"};
}

// 403
IrcResponse	ERR_NOSUCHCHANNEL()
{
	return (IrcResponse){"403", "No such channel"};
}

// 404
IrcResponse	ERR_CANNOTSENDTOCHAN()
{
	return (IrcResponse){"404", "Cannot send to channel"};
}

// 432
IrcResponse	ERR_ERRONEUSNICKNAME()
{
	return (IrcResponse){"432", "Nickname reserved, or containing invalid characters. Please stick to these : [A-Z, a-z, -, _]"};
}

// 433
IrcResponse	ERR_NICKNAMEINUSE(string_t nickname)
{
	return (IrcResponse){"433", nickname + " :Nickname is already in use"};
}

// 451
IrcResponse	ERR_NOTREGISTERED()
{
	return (IrcResponse){"451", "You must first authenticate"};
}

/* ************************************************************************** */
