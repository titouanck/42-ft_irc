/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:31:22 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/13 02:31:40 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "connections.hpp"

/* COMPULSORY MEMBERS OF THE ORTHODOX CANONICAL CLASS *********************** */

Client::Client()
{
	pthread_mutex_init(&this->_mutex, NULL);
}

Client::Client(const Client &copy)
{
	*this = copy;
}

Client &Client::operator=(const Client &copy)
{
	Client	*copyPtr;
	int		size;
	
	copyPtr = const_cast<Client *>(&copy);
	size = sizeof(Client);
	for (int i = 0; i < size; i++)
		reinterpret_cast<char *>(this)[i] = reinterpret_cast<char *>(copyPtr)[i];
	return *this;
}

Client::~Client()
{
	pthread_mutex_destroy(&this->_mutex);
}

/* SETTERS ****************************************************************** */

void	Client::setIndex(unsigned int index)
{
	this->_index = index;
}

void	Client::setIdentity()
{
	std::ostringstream	oss;
	string_t			ip;
	string_t			name;

	inet_ntop(AF_INET6, &(this->addr.sin6_addr), this->_ip, INET6_ADDRSTRLEN);
	if (getnameinfo((struct sockaddr*)&addr, sizeof(addr), this->_name, NI_MAXHOST, NULL, 0, 0) != 0)
		this->_name[0] = '\0';
	ip = this->getIp();
	name = this->getName();
	if (ip.compare(name) != 0 && name.length() > 0)
	{
		if (ip.length() >= 7 && ip.substr(0, 7) == "::ffff:")
			ip = ip.substr(7);
		oss << name;
	}
	else
	{
		if (ip.length() >= 7 && ip.substr(0, 7) == "::ffff:")
			ip = ip.substr(7);
		oss << ip;
	}
	this->_pingTime = std::time(0);
	this->_pinged = true;
	this->_identity = oss.str();
}

void	Client::setOperator(bool isOp)
{
	this->_operator = isOp;
}

void	Client::PASS(string_t passphrase)
{
	if (this->_authenticated || passphrase.compare(IRC::server->getPassword()) != 0)
		removeConn(*this);
	else
	{
		this->_authenticated = true;
		this->_pinged = false;
	}
}

void	Client::NICK(string_t nickname)
{
	if (!this->isAuthenticated() || this->_nickname.compare(nickname) == 0)
		return ;
	pthread_mutex_lock(&IRC::nickLst_mutex);
	if (IRC::nickLst.find(nickname) == IRC::nickLst.end())
	{
		if (this->_nickname.length() != 0)
			IRC::nickLst.erase(this->_nickname);
		IRC::nickLst.insert(IRC::nickLst.end(), nickname);
		this->_nickname = nickname;
	}
	pthread_mutex_unlock(&IRC::nickLst_mutex);
	this->_nickname = nickname;
}

void	Client::USER(string_t content)
{
	string_t			username;
	string_t			realname;
	size_t				pos;

	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return ;
	username = content.substr(0, pos);
	content = lTrim(content.substr(pos));

	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return ;
	// hostname = content.substr(0, pos);
	content = lTrim(content.substr(pos));

	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return ;
	// servname = content.substr(0, pos);
	content = lTrim(content.substr(pos));

	if (content.c_str()[0] != ':')
		return ;
	realname = rTrim(content.substr(1));
	if (!!realname.length())
		return ;
	this->_username = username;
	this->_realname = realname;
}

/* ************************************************************************** */

void	Client::lockMutex()
{
	pthread_mutex_lock(&this->_mutex);
}

void	Client::unlockMutex()
{
	pthread_mutex_unlock(&this->_mutex);
}

/* GETTERS ******************************************************************* */

unsigned int	Client::getIndex() const
{
	return this->_index;
}

string_t	Client::getIp() const
{
	return this->_ip;
}

string_t	Client::getName() const
{
	return this->_name;
}

string_t	Client::getIdentity() const
{
	return this->_identity;
}

std::time_t Client::getPingTime() const
{
	return this->_pingTime;
}

bool	Client::isPinged() const
{
	return this->_pinged;
}

bool	Client::isOperator() const
{
	return this->_operator;
}

bool	Client::isAuthenticated() const
{
	return this->_authenticated;
}

string_t	Client::getNickname() const
{
	return this->_nickname;
}

string_t	Client::getUsername() const
{
	return this->_username;
}

string_t	Client::getRealname() const
{
	return this->_realname;
}


/* ************************************************************************** */
