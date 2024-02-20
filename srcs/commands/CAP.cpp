/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:26:26 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:42:40 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "utils/ircResponses.hpp"

/* ************************************************************************** */

void	Client::CAP(string_t content)
{
	(void)	content;
	this->sendMessage(formatReference("", (IrcResponse){"CAP * LS", ""}));
}
