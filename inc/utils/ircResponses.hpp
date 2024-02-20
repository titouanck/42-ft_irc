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
	#include "utils/types.hpp"
	#include "utils/utils.hpp"
	#include "classes/Client.hpp"

/* ************************************************************************** */

string_t		formatReference(string_t nickname, IrcResponse ref);
string_t		welcomeBurst(Client &client);

IrcResponse	ERR_NOTREGISTERED();
IrcResponse	ERR_NICKNAMEINUSE(string_t nickname);
IrcResponse	ERR_ERRONEUSNICKNAME();
IrcResponse	ERR_NOSUCHNICK();
IrcResponse	ERR_NOSUCHCHANNEL();
IrcResponse	ERR_CANNOTSENDTOCHAN();

/* ************************************************************************** */

#endif
