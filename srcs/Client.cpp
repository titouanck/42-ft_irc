/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:31:22 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/19 19:55:35 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "newConn.hpp"
#include "numericReferences.hpp"
#include "Channel.hpp"

/* STATIC VARIABLES ********************************************************** */

std::map<string_t, Client *>	Client::nicknames;
pthread_mutex_t					Client::nicknames_mutex;

/* COMPULSORY MEMBERS OF THE ORTHODOX CANONICAL CLASS *********************** */

Client::Client() : _channels()
{
	pthread_mutex_init(&this->_mutex, NULL);
	this->_channels.insert("bonjour");
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

/* COMMANDS ***************************************************************** */

void	Client::PASS(string_t passphrase)
{
	if (this->_authenticated || passphrase.compare(Server::getPassword()) != 0)
		this->disconnect();
	else
	{
		this->_authenticated = true;
		this->_pinged = false;
	}
}

void	Client::NICK(string_t nickname)
{
	bool	sendWelcomeBurst;

	sendWelcomeBurst = false;
	transform(nickname.begin(), nickname.end(), nickname.begin(), tolower);
	if (!this->isAuthenticated())
		return this->sendMessage(formatReference(GUEST, ERR_NOTREGISTERED()));
	else if (this->_nickname.compare(nickname) == 0)
		return ;
	nickname = rTrim(nickname.substr(0, nickname.find(':')));
	if (!checkStrValidity(nickname) || nickname.compare(GUEST) == 0)
		return this->sendMessage(formatReference(GUEST, ERR_ERRONEUSNICKNAME()));
	pthread_mutex_lock(&nicknames_mutex);
	if (nicknames.find(nickname) == nicknames.end())
	{
		if (this->_nickname.length() == 0)
			sendWelcomeBurst = true;
		else
			nicknames.erase(this->_nickname);
		nicknames[nickname] = this;
		this->_nickname = nickname;
		if (sendWelcomeBurst)
		{
			this->sendMessage(welcomeBurst(*this));
			sendWelcomeBurst = false;
		}
	}
	else
		this->sendMessage(formatReference(GUEST, ERR_NICKNAMEINUSE(nickname)));
	pthread_mutex_unlock(&nicknames_mutex);
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
	if (!realname.length())
		return ;
	this->_username = username;
	this->_realname = realname;
}

void	Client::CAP(string_t content)
{
	(void)	content;
	this->sendMessage(formatReference("", (IrcReference){"CAP * LS", ""}));
}

void	Client::PING(string_t content)
{
	this->sendMessage("PONG " + content + "\n");
}

void	Client::PONG(string_t content)
{
	if (content.length() > 1 && content[0] == ':')
		content = content.substr(1);
	if (content.compare(this->_pingContent) == 0)
	{
		this->_pinged = false;
		this->_pingContent = "";
	}
}

void	Client::JOIN(string_t content)
{
	std::stringstream	oss;
	string_t			remaining;
	string_t			channelKey;
	size_t				pos;
	bool				isOp;

	if (content.length() < 2 || content[0] != '#')
		return ;
	content = content.substr(1);
	pos = content.find(',');
	if (pos != std::string::npos)
		remaining = content.substr(pos + 1);
	content = content.substr(0, pos);
	pos = content.find_first_of(" \t");
	if (pos != std::string::npos)
		channelKey = content.substr(pos + 1);
	content = content.substr(0, pos);
	if (!checkStrValidity(content))
		return ;
	transform(content.begin(), content.end(), content.begin(), tolower);
	oss << ":" << this->_nickname;
	if (this->_username.length() > 0)
		oss << "!" << this->_username;
	oss << "@" << g_servername << " JOIN #" << content << '\n';
	if (g_channels.find(content) == g_channels.end())	/* If channel doesn't exist */
	{
		g_channels[content] = Channel();
		g_channels[content].setName(content);
		oss << formatReference(this->_nickname + " = #" + content, (IrcReference){"353", "@" + this->_nickname});
		isOp = true;
	}
	else 												/* If channel does exist */
	{
		oss << formatReference(this->_nickname + " = #" + content, RPL_NAMREPLY(this->_nickname, g_channels[content].getUsers()));
		isOp = false;
	}
	
	if (this->_channels.find(content) == this->_channels.end())
	{
		oss << formatReference(this->_nickname + " #" + content, (IrcReference){"366", "End of /NAMES list"});
		this->sendMessage(oss.str());
		this->_channels.insert(content);
		g_channels[content].connect(this);
		if (isOp)
			g_channels[content].op(this);
	}
	this->JOIN(lTrim(remaining));
}

void	Client::PART(string_t content)
{
	string_t			channelToLeave;

	if (content.length() < 2 || content[0] != '#')
		return ;
	else
		content = content.substr(1);
	channelToLeave = rTrim(content);
	transform(channelToLeave.begin(), channelToLeave.end(), channelToLeave.begin(), tolower);
	if (g_channels.find(channelToLeave) != g_channels.end() && this->_channels.find(channelToLeave) != this->_channels.end())
	{
		g_channels[channelToLeave].disconnect(this);
		this->_channels.erase(channelToLeave);
		this->sendMessage(formatIrcMessage(this->getFullname(), "#" + channelToLeave, "PART", content));
	}
}

void	Client::KICK(string_t content)
{
	string_t		givenChannel;
	string_t		givenNickname;
	size_t			pos;

	if (content.length() < 2 || content[0] != '#')
		return ;
	else
		content = content.substr(1);
	
	pos = content.find_first_of(" \t");
	if (pos == std::string::npos)
		return ;
	givenChannel = content.substr(0, pos);
	content = content.substr(pos + 1);

	pos = content.find(':');
	givenNickname = rTrim(content.substr(0, pos));
	if (givenNickname.length() == 0)
		return ;
	if (pos != std::string::npos)
		content = content.substr(pos + 1);
	else
		content = "";

	transform(givenChannel.begin(), givenChannel.end(), givenChannel.begin(), tolower);
	transform(givenNickname.begin(), givenNickname.end(), givenNickname.begin(), tolower);
	
	if (g_channels.find(givenChannel) != g_channels.end() && g_channels[givenChannel].isOp(this) && nicknames.find(givenNickname) != nicknames.end() && !g_channels[givenChannel].isOp(nicknames[givenNickname]))
	{
		nicknames[givenNickname]->_channels.erase(givenChannel);
		g_channels[givenChannel].disconnect(nicknames[givenNickname]);
		nicknames[givenNickname]->sendMessage(formatIrcMessage(this->getFullname(), "#" + givenChannel + " " + givenNickname, "KICK", content));
	}
}

void	Client::TOPIC(string_t content)
{
	size_t			pos;
	string_t		givenChannel;
	
	if (content.length() < 2 || content[0] != '#')
		return ;
	else
		content = content.substr(1);
	pos = content.find_first_of(" \t");
	givenChannel = content.substr(0, pos);
	transform(givenChannel.begin(), givenChannel.end(), givenChannel.begin(), tolower);
	if (pos == std::string::npos)
	{
		if (g_channels.find(givenChannel) != g_channels.end())
			this->sendMessage(formatReference(this->_nickname + " #" + givenChannel, RPL_TOPIC(g_channels[givenChannel])));
		else
			this->sendMessage(formatReference(this->_nickname + " #" + givenChannel, ERR_NOSUCHCHANNEL()));
		return ;
	}
	// givenChannel = content.substr(0, pos);
	// content = content.substr(pos + 1);
}

void	Client::PRIVMSG(string_t content)
{
	bool				isChannelName;
	string_t			receiver;
	size_t				pos;

	if (content.length() > 2 && content[0] == '#')
		isChannelName = true;
	else
		isChannelName = false;
	pos = content.find(':');
	if (pos == std::string::npos)
		return ;
	receiver = rTrim(content.substr(0, pos));
	transform(receiver.begin(), receiver.end(), receiver.begin(), tolower);
	content = content.substr(pos + 1);
	
	if (!isChannelName)
	{
		if (receiver.compare(this->_nickname) == 0)
			return ;
		if (nicknames.find(receiver) != nicknames.end())
			nicknames[receiver]->sendMessage(formatIrcMessage(this->getFullname(), receiver, "PRIVMSG", content));
		else
			this->sendMessage(formatReference(this->_nickname + " " + receiver, ERR_NOSUCHNICK()));
	}
	else if (isChannelName)
	{
		if (g_channels.find(receiver.substr(1)) != g_channels.end())
		{
			if (g_channels[receiver.substr(1)].isConnected(this))
				g_channels[receiver.substr(1)].sendMessage(this, formatIrcMessage(this->getFullname(), receiver, "PRIVMSG", content));
			else
				this->sendMessage(formatReference(this->_nickname + " " + receiver, ERR_CANNOTSENDTOCHAN()));
		}
		else
			this->sendMessage(formatReference(this->_nickname + " " + receiver, ERR_NOSUCHCHANNEL()));
	}
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
			if (g_channels[*it].getSize() == 0)
				g_channels.erase(*it);
		}
	}
	if (this->_nickname.length() > 0)
		nicknames.erase(this->_nickname);
	close(pollfd.fd);
	bzero(&pollfd, sizeof(pollfd));
	printConn('-', *this);
	bzero(this, sizeof(*this));
}

void	Client::sendMessage(string_t content)
{
	send(g_pollfds[this->_index].fd, content.c_str(), content.length(), 0);
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
	if (this->getUsername().length() == 0)
		return this->_nickname;
	else
		return this->_nickname + "!" + this->_username;
}

string_t	Client::getPingContent() const
{
	return this->_pingContent;
}

/* ************************************************************************** */
