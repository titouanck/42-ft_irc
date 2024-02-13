/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:19:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/12 15:03:43 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

/* STATIC VARIABLES ********************************************************* */

Server*				IRC::server		= 0;
pollfd_t*			IRC::pollfds	= 0;
Client*				IRC::clients	= 0;

std::set<string_t>	IRC::nickLst;
pthread_mutex_t		IRC::nickLst_mutex;

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
