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

/* ************************************************************************** */

string_t	formatIrcMessage(string_t fullName, string_t channel, string_t command, string_t content)
{
	return ":" + fullName + "@" + g_servername + " " + command + " " + channel + " :" + content + "\n";
}

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

	str += formatReference(nickname, RPL_WELCOME(client));
	str += formatReference(nickname, RPL_YOURHOST());
	str += formatReference(nickname, RPL_CREATED());
	str += formatReference(nickname, RPL_MYINFO());
	str += formatReference(nickname, RPL_MOTDSTART());
	str += formatReference(nickname, RPL_MOTD());
	str += formatReference(nickname, RPL_ENDOFMOTD());
	return str;
}

/* REFERENCES *************************************************************** */

// 001
IrcResponse	RPL_WELCOME(Client &client)
{
	std::ostringstream	oss;

	oss << "Welcome to the " << getMyHostname() << " Network, " << client.getNickname();
	return (IrcResponse){"001", oss.str()};
}

// 002
IrcResponse	RPL_YOURHOST()
{
	std::ostringstream	oss;

	oss << "Your host is " << g_servername << ", running version " << g_serversion;
	return (IrcResponse){"002", oss.str()};
}

// 003
IrcResponse	RPL_CREATED()
{
	std::ostringstream	oss;

	oss << "This server was created " << formatTime(Server::launchTime);
	return (IrcResponse){"003", oss.str()};
}

// 004
IrcResponse	RPL_MYINFO()
{
	return (IrcResponse){"004", "-"};
}

// 332
IrcResponse	RPL_TOPIC(Channel &channel)
{
	return (IrcResponse){"332", channel.getTopic()};
}
	
// 353
IrcResponse	RPL_NAMREPLY(string_t nickname, const std::map<Client *, bool>	&users)
{
	std::ostringstream							oss;
	std::map<Client *, bool>::const_iterator	it;

	oss << nickname;
	for (it = users.begin(); it != users.end(); ++it)
	{
		oss << ' ';
		if (it->second == ISOP)
			oss << '@';
		oss << it->first->getNickname();
	}
	return (IrcResponse){"353", oss.str()};
}

// 372
IrcResponse	RPL_MOTD()
{
	return (IrcResponse){"372", "-"};
}

// 375
IrcResponse	RPL_MOTDSTART()
{
	return (IrcResponse){"375", "You are in a maze of twisty passages, all alike."};
}

// 376
IrcResponse	RPL_ENDOFMOTD()
{
	return (IrcResponse){"376", ">"};
}

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
