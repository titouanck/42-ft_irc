/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:29:17 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/26 17:04:43 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
	#define CLIENT_HPP
	#include "utils/types.hpp"
	#include <set>

	class Server;
	class Channel;

/* ************************************************************************** */

class Client
{
	public:
		Client();
		Client(const Client &copy);
		Client &operator=(const Client &copy);
		~Client();
		
		void			sendMessage(string_t content);
		void			disconnect();
		void			appendToBuffer(string_t toAppend);
		void			clearBuffer();

		void			setIndex(unsigned int index);
		void			setIdentity();
		void			setOperator(bool isOp);
		void			setPingContent(string_t content);
	
		unsigned int	getIndex() const;
		string_t		getIp() const;
		string_t		getName() const;
		string_t		getIdentity() const;
		std::time_t 	getPingTime() const;
		bool			isPinged() const;
		bool			isOperator() const;
		bool			isAuthenticated() const;
		string_t		getNickname() const;
		string_t		getUsername() const;
		string_t		getRealname() const;
		string_t		getFullname() const;
		string_t		getPingContent() const;
		string_t		getBuffer() const;

		void			PASS(string_t passphrase);
		void			NICK(string_t nickname);
		void			USER(string_t content);
		void			CAP(string_t content);
		void			PING(string_t content);
		void			PONG(string_t content);
		void			JOIN(string_t content);
		void			PART(string_t content);
		void			KICK(string_t content);
		void			PRIVMSG(string_t content);
		void			TOPIC(string_t content);
		void			MODE(string_t content);

		sockaddr_in6_t	addr;
		socklen_t		len;

		std::set<string_t>					_channels;
		static std::map<string_t, Client *>	nicknames;

	private:
		unsigned int					_index;
		char							_ip[INET6_ADDRSTRLEN];
		char							_name[NI_MAXHOST];
		string_t						_identity;
		std::time_t 					_pingTime;
		bool							_pinged;
		string_t						_pingContent;
		bool							_operator;
		bool							_authenticated;
		string_t						_buffer;
		string_t						_nickname;
		string_t						_username;
		string_t						_realname;
};

/* ************************************************************************** */

#endif
