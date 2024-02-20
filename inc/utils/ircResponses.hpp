/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircResponses.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:43:41 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/19 19:55:02 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCRESPONSES_HPP
	#define IRCRESPONSES_HPP
	#include "types.hpp"
	#include "utils/utils.hpp"
	#include "classes/Client.hpp"

/* ************************************************************************** */

string_t		formatIrcMessage(string_t fullName, string_t channel, string_t command, string_t content);
string_t		formatReference(string_t nickname, IrcResponse ref);
string_t		welcomeBurst(Client &client);
IrcResponse	RPL_WELCOME(Client &client);
IrcResponse	RPL_YOURHOST();
IrcResponse	RPL_CREATED();
IrcResponse	RPL_MYINFO();
IrcResponse	RPL_MOTD();
IrcResponse	RPL_MOTDSTART();
IrcResponse	RPL_ENDOFMOTD();
IrcResponse	ERR_NOTREGISTERED();
IrcResponse	ERR_NICKNAMEINUSE(string_t nickname);
IrcResponse	ERR_ERRONEUSNICKNAME();
IrcResponse	RPL_NAMREPLY(string_t nickname, const std::map<Client *, bool>	&users);
IrcResponse	ERR_NOSUCHNICK();
IrcResponse	ERR_NOSUCHCHANNEL();
IrcResponse	ERR_CANNOTSENDTOCHAN();
IrcResponse	RPL_TOPIC(Channel &channel);

/* ************************************************************************** */

#endif
