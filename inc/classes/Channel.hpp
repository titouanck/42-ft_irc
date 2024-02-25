/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:34:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/25 18:36:42 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
    #define CHANNEL_HPP
	#include "utils/types.hpp"
	
	#define ISOP true
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

		bool							connect(Client *client);
		void							disconnect(Client *client);
		void							sendMessage(Client *client, string_t content);

		void					   		setName(string_t name);
		void					   		setTopic(Client *client, string_t name);
		void							op(Client *client);
		void							deop(Client *client);
		void							setInviteOnly(bool value);
		void							setTopicRestricted(bool value);
		void							setChannelKey(string_t key);
	
		const std::map<Client *, bool>	&getUsers() const;
		string_t						getName() const;
		string_t						getUserList() const;
		string_t						getTopic() const;
		string_t						getTopicWhoTime() const;
		bool							isOp(Client *client) const;
		bool							isConnected(Client *client) const;
		bool							isInviteOnly() const;
		bool							isTopicRestricted() const;
		string_t						getChannelKey() const;
		bool							isInvited(Client *client) const;

	private:
		string_t					_name;
		string_t					_topic;
		std::map<Client *, bool>	_users;
		std::map<Client *, time_t>	_invitedUsers;
		string_t					_whoChangedTopic;
		time_t						_timeTopicChanged;
		bool						_inviteOnly;
		bool						_topicRestricted;
		string_t					_channelKey;
};

/* ************************************************************************** */

#endif

