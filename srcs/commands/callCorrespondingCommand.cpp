/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callCorrespondingCommand.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:12:44 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/27 14:57:30 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/callCorrespondingCommand.hpp"
#include "core/routine.hpp"
#include "classes/Client.hpp"
#include "utils/ircNumerics.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

void	callCorrespondingCommand(Client &client, Message message)
{
	if (message.command.length() == 0);
	else if (message.command.compare("QUIT") == 0)
	{
		std::cout << "----------------------------------------" << '\n';
		client.disconnect();
	}
	else if (message.command.compare("CAP") == 0)
		client.CAP(message.content);
	else if (message.command.compare("PASS") == 0)
		client.PASS(message.content);
	else if (message.command.compare("USER") == 0)
		client.USER(message.content);
	// else if (!(client.isAuthenticated()))
	// 	return client.sendMessage(formatIrcMessage(g_servername, ERR_NOTREGISTERED, GUEST, "You must first authenticate"));
	else if (message.command.compare("NICK") == 0)
		client.NICK(message.content);
	// else if (client.getNickname().length() == 0)
	// 	return client.sendMessage(formatIrcMessage(g_servername, ERR_NONICKNAMEGIVEN, GUEST, "You must first set a nickname"));
	else if (message.command.compare("PING") == 0)
		client.PING(message.content);
	else if (message.command.compare("PONG") == 0)
		client.PONG(message.content);
	else if (message.command.compare("JOIN") == 0)
		client.JOIN(message.content);
	else if (message.command.compare("PART") == 0)
		client.PART(message.content);
	else if (message.command.compare("KICK") == 0)
		client.KICK(message.content);
	else if (message.command.compare("PRIVMSG") == 0)
		client.PRIVMSG(message.content);
	else if (message.command.compare("TOPIC") == 0)
		client.TOPIC(message.content);
	else if (message.command.compare("MODE") == 0)
		client.MODE(message.content);
}
