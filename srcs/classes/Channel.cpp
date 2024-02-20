/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:46:34 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 13:25:55 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Channel.hpp"
#include "classes/Client.hpp"

/* COMPULSORY MEMBERS OF THE ORTHODOX CANONICAL CLASS *********************** */

Channel::Channel()
{
}

Channel::Channel(const Channel &copy)
{
	*this = copy;
}

Channel &Channel::operator=(const Channel &copy)
{
	(void)	copy;
	return *this;
}

Channel::~Channel()
{
}

/* CHANNEL CONNECTIONS ****************************************************** */

void	Channel::connect(Client *client)
{
	if (this->_users.find(client) == this->_users.end())
		this->_users[client] = ISNOTOP;
}

void	Channel::disconnect(Client *client)
{
	if (this->_users.find(client) != this->_users.end())
		this->_users.erase(client);
}

/* DATA TRANSMISSION ******************************************************** */

void	Channel::sendMessage(Client *client, string_t content)
{
	std::map<Client *, bool>::iterator it;

	for (it = this->_users.begin(); it != this->_users.end(); it++)
	{
		if (it->first != client)
			(it->first)->sendMessage(content);
	}
}

/* SETTERS ****************************************************************** */

void	Channel::setName(string_t name)
{
	this->_name = name;
}

void	Channel::setTopic(string_t topic)
{
	this->_topic = topic;
}

void	Channel::op(Client *client)
{
	std::map<Client *, bool>::iterator it;

	it = this->_users.find(client);
	if (it != this->_users.end())
		it->second = ISOP;
}

void	Channel::deop(Client *client)
{
	std::map<Client *, bool>::iterator it;

	it = this->_users.find(client);
	if (it != this->_users.end())
		it->second = ISNOTOP;
}

/* GETTERS ****************************************************************** */

string_t	Channel::getTopic() const
{
	return this->_topic;
}

const std::map<Client *, bool>	&Channel::getUsers() const
{
	return this->_users;
}

string_t	Channel::getName() const
{
	return this->_name;
}

string_t	Channel::getUserList() const
{
	std::ostringstream							oss;
	std::map<Client *, bool>::const_iterator	it;

	for (it = this->_users.begin(); it != this->_users.end(); ++it)
	{
		if (it != this->_users.begin())
			oss << ' ';
		if (it->second == ISOP)
			oss << '@';
		oss << it->first->getNickname();
	}
	return oss.str();
}

bool	Channel::isOp(Client *client) const
{
	std::map<Client *, bool>::const_iterator it;

	it = this->_users.find(client);
	if (it != this->_users.end())
		return it->second;
	return false;
}

bool	Channel::isConnected(Client *client) const
{
	std::map<Client *, bool>::const_iterator it;

	it = this->_users.find(client);
	if (it != this->_users.end())
		return true;
	return false;
}
