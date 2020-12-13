/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 13:31:41 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/13 14:12:21 by jkoers        ########   odam.nl         */
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

ssize_t		ft_min(ssize_t a, ssize_t b)
{
	return (a < b ? a : b);
}

void	putstr(char *str)
{
	write(1, str, strlen(str));
}

void	putstr_cat(char *str, size_t size)
{
	while (size > 0)
	{
		size--;
		if (*str == '\n')
			putstr("\\n");
		else 
			write(1, str, 1);
		str++;
	}
}

void	writebuf(t_buf *fd)
{
	putstr("limit <");
	putstr_cat(fd->data + fd->start, fd->size < 0 ? 0 : (size_t)fd->size);
	putstr(">\n");
	
	putstr("full  <");
	putstr_cat(fd->data, BUFF_SIZE);
	putstr(">\n");
}

void	*ft_memcpy(void *dest, void *src, ssize_t n)
{
	unsigned char *d;
	unsigned char *s;

	if (dest == NULL || src == NULL || dest == src)
		return (dest);
	d = dest;
	s = src;
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
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
	t_buf	*tmp;
	
	i = 0;
	if (total_size <= 0 || (*fd)->size < 0)
		return (-1);
	*line = malloc((size_t)(total_size + 1));
	(*line)[total_size] = '\0';
	while ((*fd)->next != NULL)
	{
		ft_memcpy(*line + i, (*fd)->data + (*fd)->start, ft_min(total_size, (*fd)->size));
		i += ft_min(total_size, (*fd)->size);
		tmp = *fd;
		*fd = (*fd)->next;
		free(tmp->data);
		free(tmp);
	}
	ft_memcpy(*line + i, (*fd)->data + (*fd)->start, ft_min(total_size - i, (*fd)->size));
	i = i == 0 ? total_size : total_size - i;
	while (i < (*fd)->size && (*fd)->data[i + (*fd)->start] == '\n')
		i++;
	(*fd)->start = i;
	(*fd)->size = (*fd)->size - i;
	(*fd)->next = NULL;
	return (1); 
}

int		get_next_line(const int fd, char **line)
{
	static t_buf	*fds[50];
	t_buf			*cur;
	ssize_t			total_size;
	
	// putstr("\n\nSTART\n");
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
