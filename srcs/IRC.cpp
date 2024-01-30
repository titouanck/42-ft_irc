/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:19:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/30 16:25:12 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

/* STATIC VARIABLES ********************************************************* */

Server*		IRC::server		= 0;
pollfd_t*	IRC::pollfds	= 0;
Client*		IRC::clients	= 0;

/* COMPULSORY MEMBERS OF THE ORTHODOX CANONICAL CLASS *********************** */

IRC::IRC()
{	/* PRIVATE */
}

IRC::IRC(const IRC &copy)
{	/* PRIVATE */
	*this = copy;
}

IRC &IRC::operator=(const IRC &copy)
{	/* PRIVATE */
	(void) copy;
	return *this;
}

IRC::~IRC()
{	/* PRIVATE */
}

/* ************************************************************************** */
