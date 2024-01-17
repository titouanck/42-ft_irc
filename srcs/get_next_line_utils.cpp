/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titouanck <chevrier.titouan@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:30:06 by tchevrie          #+#    #+#             */
/*   Updated: 2024/01/17 17:17:32 by titouanck        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_bufferList	*ftlst_new_buffer(void)
{
	t_bufferList	*new_buffer;

	new_buffer = (t_bufferList *) malloc(sizeof(t_bufferList));
	if (!new_buffer)
		return (NULL);
	new_buffer->content = (char *) malloc(BUFFER_SIZE + 1);
	if (!(new_buffer->content))
	{
		free(new_buffer);
		return NULL;
	}
	(new_buffer->content)[0] = '\0';
	new_buffer->next = 0;
	return (new_buffer);
}

t_fdList	*ftlst_new_fd(int fd)
{
	t_fdList	*_new;

	_new = (t_fdList *) malloc(sizeof(t_fdList));
	if (!_new)
		return (NULL);
	_new->fd = fd;
	_new->begin = ftlst_new_buffer();
	if (!(_new->begin))
	{
		free(_new);
		return NULL;
	}
	_new->next_fd = 0;
	return (_new);
}

int	end_of_line(char *content)
{
	size_t	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	count_memory(t_bufferList *current)
{
	size_t	memory;
	size_t	i;

	memory = 1;
	while (current)
	{
		i = 0;
		while ((current->content)[i])
		{
			memory++;
			i++;
			if ((current->content)[i - 1] == '\n')
				break ;
		}
		if (i > 0 && (current->content)[i - 1] == '\n')
		{
			i++;
			break ;
		}
		current = current->next;
	}
	return (memory);
}

t_fdList	*clean_fd_list(t_fdList *fd_list, t_fdList *c_fd)
{
	t_fdList	*tmp;

	if (!((c_fd->begin->content)[0]))
	{
		free(c_fd->begin->content);
		free(c_fd->begin);
		if (fd_list == c_fd)
			fd_list = fd_list->next_fd;
		else
		{
			tmp = fd_list;
			while (tmp->next_fd && tmp->next_fd != c_fd)
				tmp = tmp->next_fd;
			if (tmp->next_fd)
				tmp->next_fd = tmp->next_fd->next_fd;
		}
		free(c_fd);
	}
	return (fd_list);
}
