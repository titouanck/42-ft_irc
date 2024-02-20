/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMyHostname.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:56:11 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 01:01:51 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"

/* ************************************************************************** */

string_t	getMyHostname()
{
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0)
		return hostname;
    return "";
}
