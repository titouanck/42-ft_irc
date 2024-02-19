/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:34:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/19 17:41:54 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
    #define CHANNEL_HPP
	#include "types.hpp"
	#include <vector>
	
	#define OPERATOR true
	#define ISNOTOP false

	class Client;

/* ************************************************************************** */

class Channel
{
	public:
		Channel();
		Channel(const Channel &copy);
		Channel &operator=(const Channel &copy);
		~Channel();

		void							connect(Client *client);
		void							disconnect(Client *client);
		void							sendMessage(Client *client, string_t content);
		void					   		setName(string_t name);
		void							op(Client *client);
		void							deop(Client *client);
		size_t							getSize() const;
		const std::map<Client *, bool>	&getUsers() const;
		bool							isOp(Client *client) const;
		bool							isConnected(Client *client) const;

	private:
		
		string_t					_name;
		std::map<Client *, bool>	_users;
};

/* ************************************************************************** */

#endif

