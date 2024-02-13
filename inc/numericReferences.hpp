/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReferences.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:43:41 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/13 21:53:56 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICREFERENCES_HPP
	#define NUMERICREFERENCES_HPP
	#include "types.hpp"
	#include "tools.hpp"
	#include "Client.hpp"

/* ************************************************************************** */

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
IrcReference	ERR_NICKNAMEINUSE();
IrcReference	ERR_ERRONEUSNICKNAME();

/* ************************************************************************** */

#endif
