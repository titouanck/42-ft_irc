/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircNumerics.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:02:16 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/20 05:18:22 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCNUMERICS_HPP
	#define IRCNUMERICS_HPP

/* ************************************************************************** */

enum IRCNUMERICS
{
	RPL_WELCOME = 001,
	RPL_YOURHOST = 002,
	RPL_CREATED = 003,
	RPL_MYINFO = 004,

	RPL_TOPIC = 332,

	RPL_NAMREPLY = 353,

	RPL_ENDOFNAMES = 366,

	RPL_MOTD = 372,

	RPL_MOTDSTART = 375,
	RPL_ENDOFMOTD = 376,

	ERR_NOSUCHNICK = 401,

	ERR_NOSUCHCHANNEL = 403,
	ERR_CANNOTSENDTOCHAN = 404,
	
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,

	ERR_NOTREGISTERED = 451
};

/* ************************************************************************** */

#endif