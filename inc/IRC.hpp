/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:17:34 by titouanck         #+#    #+#             */
/*   Updated: 2024/01/30 16:26:05 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
	#define IRC_HPP
	#include "typedef.hpp"

/* ************************************************************************** */

class IRC
{
	public:
		static Server	*server;
		static pollfd_t	*pollfds;
		static Client	*clients;

	private:
		IRC();
		IRC(const IRC &copy);
		IRC &operator=(const IRC &copy);
		~IRC();
};

/* ************************************************************************** */

#endif