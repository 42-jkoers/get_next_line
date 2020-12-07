/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 13:31:41 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/07 23:52:12 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <sys/select.h>
#include <stdlib.h>
#include <fcntl.h>

#include <stdio.h>

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;

	if (dest == NULL || src == NULL)
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

ssize_t	strchr_i(char *str, char c, size_t len)
{
	ssize_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_buf	*new_buf(ssize_t size)
{
	t_buf	*new_buf;

	new_buf = malloc(sizeof(t_buf));
	new_buf->content = malloc(size);
	new_buf->size = size;
	new_buf->next = NULL;
	return (new_buf);
}

char 	*malloc_line(t_buf *fd, ssize_t *size)
{
	size_t	total_size;
	char	*result;

	total_size = 0;
	while (fd->next != NULL)
	{
		total_size += fd->size;
		fd = fd->next;
	}
	*size = strchr_i((char *)(fd->content), '\n', fd->size);
	if (*size == -1)
		*size = fd->size;
	total_size += *size;
	result = malloc(total_size + 1);
	if (result != NULL)
		result[total_size] = '\0';
	return (result);
}

int		join(t_buf *fd, char **line)
{
	size_t	i;
	t_buf	*tmp;
	ssize_t	size;

	i = 0;
	*line = malloc_line(fd, &size);			
	while (fd->next != NULL)
	{
		ft_memcpy(*line + i, fd->content, fd->size);
		i += fd->size;
		tmp = fd;
		fd = fd->next;
		free(tmp->content);
		free(tmp);
	}
	ft_memcpy(*line + i, fd->content, size);
	while (size < fd->size && ((char *)(fd->content))[size] == '\n')
		size++;
	ft_memcpy(fd->content, fd->content + size, fd->size - size);
	fd->size = fd->size - size;
	fd->next = NULL;
	return (fd->size != size); 
}

int		get_next_line(const int fd, char **line)
{
	static t_buf	*fds[50];
	t_buf			*cur;
	ssize_t			read_len;

	if (fd < 0)
		return (-1);
	if (!fds[fd])
		fds[fd] = new_buf(BUFF_SIZE);
	else if (strchr_i(fds[fd]->content, '\n', fds[fd]->size) != -1)
		return (join(fds[fd], line));
	cur = fds[fd];
	read_len = 42;
	while (read_len > 0)
	{
		read_len = read(fd, cur->content, BUFF_SIZE);
		cur->size = read_len;
		if (read_len != BUFF_SIZE)
			return (join(fds[fd], line));
		if (strchr_i((char *)cur->content, '\n', cur->size) != -1)
			return (join(fds[fd], line));
		cur->next = new_buf(BUFF_SIZE);
		cur = cur->next;
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
	while (get_next_line(fd, &line) == 1 && i < 10)
	{
		printf("<%s>\n", line);
		// free(*line);
		i++;
	}
	return 0;
}
