/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 13:29:56 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/06 21:43:56 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 20
# include <stddef.h>
# include <unistd.h>

typedef struct		s_buf
{
	void			*content;
	ssize_t			size;
	struct s_buf	*next;
}					t_buf;

int		get_next_line(int fd, char **line);

#endif
