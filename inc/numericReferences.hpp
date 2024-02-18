/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReferences.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:43:41 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/18 15:37:11 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICREFERENCES_HPP
	#define NUMERICREFERENCES_HPP
	#include "types.hpp"
	#include "tools.hpp"
	#include "Client.hpp"

/* ************************************************************************** */

string_t		formatIrcMessage(Client *client, bool isOp, string_t channel, string_t command, string_t content);
string_t		formatReference(string_t nickname, IrcReference ref);
string_t		welcomeBurst(Client &client);
IrcReference	RPL_WELCOME(Client &client);
IrcReference	RPL_YOURHOST();
IrcReference	RPL_CREATED();
IrcReference	RPL_MYINFO();
IrcReference	RPL_MOTD();
IrcReference	RPL_MOTDSTART();
IrcReference	RPL_ENDOFMOTD();
IrcReference	ERR_NOTREGISTERED();
IrcReference	ERR_NICKNAMEINUSE(string_t nickname);
IrcReference	ERR_ERRONEUSNICKNAME();
IrcReference	RPL_NAMREPLY(string_t nickname, const std::map<Client *, bool>	&users);

/* ************************************************************************** */

#endif
