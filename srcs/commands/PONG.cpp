/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 01:27:37 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 19:03:53 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"

/* ************************************************************************** */

void	Client::PONG(string_t content)
{
	if (content.length() >= 1 && content[0] == ':')
		content = content.substr(1);
	if (content.compare(this->_pingContent) == 0)
	{
		this->_pinged = false;
		this->_pingContent = "";
	}
}
