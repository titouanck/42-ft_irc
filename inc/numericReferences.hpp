/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReferences.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:43:41 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/14 15:22:03 by tchevrie         ###   ########.fr       */
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

/* ************************************************************************** */

#endif
