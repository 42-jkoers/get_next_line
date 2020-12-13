/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 13:29:56 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/13 13:37:49 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 6
# include <stddef.h>
# include <unistd.h>

typedef struct		s_buf
{
	char			*data;
	ssize_t			size;
	ssize_t			start;
	struct s_buf	*next;
}					t_buf;

int		get_next_line(int fd, char **line);

#endif
