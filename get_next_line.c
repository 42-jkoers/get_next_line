/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 13:31:41 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/13 17:47:10 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <sys/select.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

#include <stdio.h>
#include <string.h>

void	next(t_buf **fd)
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
	new_buf->data = malloc(size);
	new_buf->size = 0;
	new_buf->start = 0;
	new_buf->next = NULL;
	return (new_buf);
}

bool	found_end(t_buf *fd, ssize_t *total_size)
{
	ssize_t	i;

	if (fd == NULL)
		return (false);
	if (*total_size == 0)
	{
		i = 0;
		while (fd->data[i + fd->start] == '\n' && i < fd->size)
			i++;
		fd->start += i;
		fd->size -= i;
	}
	i = 0;
	while (i < fd->size)
	{
		if (fd->data[i + fd->start] == '\n')
			return (true);
		*total_size += 1;
		i++;
	}
	return (false);
}

int		join(t_buf **fd, ssize_t total_size, char **line)
{
	ssize_t	i;
	
	i = 0;
	if ((*fd)->size < 0)
		return (-1);
	*line = malloc((size_t)(total_size + 1));
	(*line)[total_size] = '\0';
	while ((*fd)->next != NULL)
	{
		ft_memcpy(*line + i, (*fd)->data + (*fd)->start, ft_min(total_size, (*fd)->size));
		i += ft_min(total_size, (*fd)->size);
		next(fd);
	}
	ft_memcpy(*line + i, (*fd)->data + (*fd)->start, ft_min(total_size - i, (*fd)->size));
	i = i == 0 ? total_size : total_size - i;
	while (i < (*fd)->size && (*fd)->data[i + (*fd)->start] == '\n')
		i++;
	if ((*fd)->size != BUFF_SIZE)
		next(fd);
	(*fd)->size = (*fd)->size - i;
	(*fd)->start = i;
	return (*fd ? 0 : 1); 
}

int		get_next_line(const int fd, char **line)
{
	static t_buf	*fds[50];
	t_buf			*cur;
	ssize_t			total_size;
	
	if (fd < 0 || BUFF_SIZE < 0)
		return (-1);
	total_size = 0;
	if (!fds[fd])
		fds[fd] = new_buf(0);
	else if (found_end(fds[fd], &total_size))
		return (join(&fds[fd], total_size, line));
	cur = fds[fd];
	while (cur)
	{
		cur->next = new_buf(BUFF_SIZE);
		cur = cur->next;
		cur->size = read(fd, cur->data, BUFF_SIZE);
		if (found_end(cur, &total_size) || cur->size != BUFF_SIZE)
			return (join(&fds[fd], total_size, line));
	}
	return (-1);
}

int		main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	i = 0;
	setvbuf(stdout, NULL, _IONBF, 0);
	while (get_next_line(fd, &line) == 1 && i < 10)
	{
		printf("<%s>\n", line);
		// free(line);
		i++;
	}
	return 0;
}
