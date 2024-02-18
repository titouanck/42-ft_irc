/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReferences.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:38:12 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/18 15:37:43 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "numericReferences.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

/* ************************************************************************** */

string_t	formatIrcMessage(Client *client, bool isOp, string_t channel, string_t command, string_t content)
{
	std::stringstream	oss;

	oss << ":";
	if (isOp)
		oss << "@";
	oss << client->getNickname() << '!';
	if (client->getUsername().length() > 0)
		oss << client->getUsername();
	else
		oss << client->getNickname();
	oss << "@" << g_servername << " " << command << " " << channel << " :" << content << '\n';
	return oss.str();
}

string_t	formatReference(string_t nickname, IrcReference ref)
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
IrcReference	RPL_WELCOME(Client &client)
{
	std::ostringstream	oss;

	oss << "Welcome to the " << getMyHostname() << " Network, " << client.getNickname();
	return (IrcReference){"001", oss.str()};
}

// 002
IrcReference	RPL_YOURHOST()
{
	std::ostringstream	oss;

	oss << "Your host is " << g_servername << ", running version " << g_serversion;
	return (IrcReference){"002", oss.str()};
}

// 003
IrcReference	RPL_CREATED()
{
	std::ostringstream	oss;

	oss << "This server was created " << formatTime(Server::launchTime);
	return (IrcReference){"003", oss.str()};
}

// 004
IrcReference	RPL_MYINFO()
{
	return (IrcReference){"004", "-"};
}

// // 005
// IrcReference	RPL_ISUPPORT()
// {
// 	return (IrcReference){"005", "<>"};
// }

// // 276
// IrcReference	RPL_WHOISCERTFP()
// {
// 	return (IrcReference){"276", "<>"};
// }
// // 311
// IrcReference	RPL_WHOISUSER()
// {
// 	return (IrcReference){"311", "<>"};
// }

// 353
IrcReference	RPL_NAMREPLY(string_t nickname, const std::map<Client *, bool>	&users)
{
	std::ostringstream							oss;
	std::map<Client *, bool>::const_iterator	it;

	oss << nickname;
	for (it = users.begin(); it != users.end(); ++it)
	{
		oss << ' ';
		if (it->second == OPERATOR)
			oss << '@';
		oss << it->first->getNickname();
	}
	return (IrcReference){"353", oss.str()};
}

// 372
IrcReference	RPL_MOTD()
{
	return (IrcReference){"372", "-"};
}

// 375
IrcReference	RPL_MOTDSTART()
{
	return (IrcReference){"375", "You are in a maze of twisty passages, all alike."};
}

// 376
IrcReference	RPL_ENDOFMOTD()
{
	return (IrcReference){"376", ">"};
}

// // 381
// IrcReference	RPL_YOUREOPER()
// {
// 	return (IrcReference){"381", "<>"};
// }

// // 422
// IrcReference	ERR_NOMOTD()
// {
// 	return (IrcReference){"422", "<>"};
// }

// 432
IrcReference	ERR_ERRONEUSNICKNAME()
{
	return (IrcReference){"432", "Nickname reserved, or containing invalid characters. Please stick to these : [A-Z, a-z, -, _]"};
}

// 433
IrcReference	ERR_NICKNAMEINUSE(string_t nickname)
{
	return (IrcReference){"433", nickname + " :Nickname is already in use"};
}

// 451
IrcReference	ERR_NOTREGISTERED()
{
	return (IrcReference){"451", "You must first authenticate"};
}

// // 481
// IrcReference	ERR_NOPRIVILEGES()
// {
// 	return (IrcReference){"481", "<>"};
// }

// // 491
// IrcReference	ERR_NOOPERHOST()
// {
// 	return (IrcReference){"491", "<>"};
// }

// // 723
// IrcReference	ERR_NOPRIVS()
// {
// 	return (IrcReference){"723", "<>"};
// }
// /* ************************************************************************** */
