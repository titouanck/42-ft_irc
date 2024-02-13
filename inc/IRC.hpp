/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:17:34 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/12 15:16:09 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
	#define IRC_HPP
	#include "typedef.hpp"
	#include <set>

/* ************************************************************************** */

class IRC
{
	public:
		static Server				*server;
		static pollfd_t				*pollfds;
		static Client				*clients;
		static std::set<string_t>	nickLst;
		static pthread_mutex_t		nickLst_mutex;

	private:
		IRC();
		IRC(const IRC &copy);
		IRC &operator=(const IRC &copy);
		~IRC();
};

/* ************************************************************************** */

#endif