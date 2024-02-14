/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 01:46:34 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/14 04:00:25 by titouanck        ###   ########.fr       */
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

void	Channel::send(Client *client, string_t content)
{
    std::vector<Client *>::iterator it;
    
    for (it = this->_users.begin(); it != this->_users.end(); it++)
    {
        if (*it == client)
            continue ;
        client->sendMessage(content);
    }
}

/* SETTERS ****************************************************************** */

void    Channel::setName(string_t name)
{
    this->_name = name;
}

