/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircNumerics.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:02:16 by tchevrie          #+#    #+#             */
/*   Updated: 2024/02/25 18:50:31 by tchevrie         ###   ########.fr       */
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

	RPL_NOTOPIC = 331,
	RPL_TOPIC = 332,
	RPL_TOPICWHOTIME = 333,

	RPL_NAMREPLY = 353,

	RPL_ENDOFNAMES = 366,

	RPL_MOTD = 372,

	RPL_MOTDSTART = 375,
	RPL_ENDOFMOTD = 376,

	ERR_NOSUCHNICK = 401,

	ERR_NOSUCHCHANNEL = 403,
	ERR_CANNOTSENDTOCHAN = 404,
	ERR_TOOMANYCHANNELS = 405,
	
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,

	ERR_NOTONCHANNEL = 442,

	ERR_NOTREGISTERED = 451,

	ERR_NEEDMOREPARAMS = 461,

	ERR_CHANNELISFULL = 471,

	ERR_INVITEONLYCHAN = 473,

	ERR_BADCHANNELKEY = 475,
	
	ERR_CHANOPRIVSNEEDED = 482
};

/* ************************************************************************** */

#endif
