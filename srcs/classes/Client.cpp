/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:31:22 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 19:26:44 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Client.hpp"
#include "classes/Server.hpp"
#include "connections/handleNewConnection.hpp"
#include "classes/Channel.hpp"
#include "connections/printConnectionStatus.hpp"

/* STATIC VARIABLES ********************************************************** */

std::map<string_t, Client *>	Client::nicknames;
pthread_mutex_t					Client::nicknames_mutex;

/* COMPULSORY MEMBERS OF THE ORTHODOX CANONICAL CLASS *********************** */

Client::Client() : _channels()
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

/* SOCKET RELATED ACTIONS *************************************************** */

void	Client::disconnect()
{
	pollfd_t	&pollfd = g_pollfds[this->_index];

	for (std::set<string_t>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it)
	{
		if (g_channels.find(*it) != g_channels.end())
		{
			g_channels[*it].disconnect(this);
			if (g_channels[*it].getUsers().size() == 0)
				g_channels.erase(*it);
		}
	}
	if (this->_nickname.length() > 0)
		nicknames.erase(this->_nickname);
	close(pollfd.fd);
	bzero(&pollfd, sizeof(pollfd));
	printConnectionStatus('-', *this);
	bzero(this, sizeof(*this));
}

void	Client::sendMessage(string_t content)
{
	send(g_pollfds[this->_index].fd, content.c_str(), content.length(), 0);
}

void	Client::appendToBuffer(string_t toAppend)
{
	this->_buffer += toAppend;
}

void	Client::clearBuffer()
{
	this->_buffer.clear();
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

void	Client::setPingContent(string_t content)
{
	this->_pingContent = content;
	this->_pingTime = std::time(0);
	this->_pinged = true;
}

/* MUTEX ******************************************************************** */

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

string_t	Client::getFullname() const
{
	string_t	fullName;

	if (this->_nickname.length() > 0)
		fullName += this->_nickname;
	if (this->_username.length() > 0)
		fullName += "!" + this->_username;
	if (this->_identity.length() > 0)
		fullName += "@" + this->_identity;
	return fullName;
}

string_t	Client::getPingContent() const
{
	return this->_pingContent;
}

string_t	Client::getBuffer() const
{
	return this->_buffer;
}

/* ************************************************************************** */
