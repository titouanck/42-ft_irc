/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:34:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/14 13:11:28 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
    #define CHANNEL_HPP
	#include "types.hpp"
	#include <vector>
	
	class Client;

/* ************************************************************************** */

class Channel
{
	public:
		Channel();
		Channel(const Channel &copy);
		Channel &operator=(const Channel &copy);
		~Channel();

		void	connect(Client *client);
		void	disconnect(Client *client);
		void	sendMessage(Client *client, string_t content);
		void    setName(string_t name);

	private:
		
		string_t				_name;
		std::vector<Client *>	_users;
};

/* ************************************************************************** */

#endif

