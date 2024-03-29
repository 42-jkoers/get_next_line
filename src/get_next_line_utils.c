/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 17:45:29 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/22 23:00:10 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

void	shift(t_buf **fd)
{
	t_buf *next;

	if (*fd == NULL)
		return ;
	next = (*fd)->next;
	if ((*fd)->data)
		free((*fd)->data);
	free(*fd);
	*fd = next;
}

t_buf	*new_buf(size_t size)
{
	t_buf	*new_buf;

	new_buf = malloc(sizeof(t_buf));
	if (new_buf == NULL)
		return (NULL);
	new_buf->data = malloc(size);
	new_buf->size = 0;
	new_buf->start = 0;
	new_buf->next = NULL;
	return (new_buf);
}
