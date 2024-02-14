/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:46:34 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/14 15:15:48 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

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
    (void)  copy;
    return  *this;
}

Channel::~Channel()
{
}

/* CHANNEL CONNECTIONS ****************************************************** */

void    Channel::connect(Client *client)
{
    std::vector<Client *>::iterator it;
    
    for (it = this->_users.begin(); it != this->_users.end(); it++)
    {
        if (*it == client)
            return ;
    }
    this->_users.insert(this->_users.end(), client);
}

void    Channel::disconnect(Client *client)
{
    std::vector<Client *>::iterator it;
    
    for (it = this->_users.begin(); it != this->_users.end(); it++)
    {
        if (*it == client)
        {
            this->_users.erase(it);
            return ;
        }
    }
}

/* DATA TRANSMISSION ******************************************************** */

void	Channel::sendMessage(Client *client, string_t content)
{
    std::vector<Client *>::iterator it;
    
    for (it = this->_users.begin(); it != this->_users.end(); it++)
    {
        if (*it != client)
            (*it)->sendMessage(content);
    }
}

/* SETTERS ****************************************************************** */

void    Channel::setName(string_t name)
{
    this->_name = name;
}

/* GETTERS ****************************************************************** */

size_t    Channel::getSize() const
{
    return this->_users.size();
}