/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printConnectionStatus.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:35:44 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/20 03:36:28 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connections/printConnectionStatus.hpp"
#include "utils/types.hpp"
#include "classes/Client.hpp"

/* ************************************************************************** */

void	printConnectionStatus(unsigned char connStatus, const Client &client)
{
	switch (connStatus)
	{
		case '+':
			std::cout << GREEN	<< "[+] client " << client.getIndex() << " (" << client.getFullname() << ")" NC << '\n';
			break ;
		case '-':
			std::cout << RED	<< "[-] client " << client.getIndex() << " (" << client.getFullname() << ")" NC << '\n';
			break ;
		case '!':
			std::cout << ORANGE	<< "[!] Cannot connect with " << client.getFullname() << ", too many clients. " RED "[> " << MAX_CLIENTS << "]" NC << '\n';
			break ;
		default:
			return ;
	}
	std::cout << "----------------------------------------" << '\n';
}
