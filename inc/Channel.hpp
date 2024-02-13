/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:34:18 by titouanck         #+#    #+#             */
/*   Updated: 2024/02/13 21:37:17 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
    #define CHANNEL_HPP
	#include "types.hpp"

/* ************************************************************************** */

class Channel
{
	public:
		Channel(string_t name);
		~Channel();

	private:
		Channel();
		Channel(const Channel &copy);
		Channel &operator=(const Channel &copy);
		  
};

/* ************************************************************************** */

#endif

