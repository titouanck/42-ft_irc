/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:26:26 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 04:50:58 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "utils/utils.hpp"

/* ************************************************************************** */

void	Client::CAP(string_t content)
{
	(void)	content;

	this->sendMessage(formatIrcMessage(g_servername, "CAP * LS", this->_nickname, "none"));
}
