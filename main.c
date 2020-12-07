/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 20:28:57 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/03 21:55:41 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "get_next_line.c"

int		main(void)
{
	int		fd;
	char	*line;
	int		code;
	int		i;

	fd = open("test.txt", O_RDONLY);
	code = 1;
	i = 0;
	while (code == 1 && i < 10)
	{
		code = get_next_line(fd, &line);
		printf("%2i <%s>\n", code, line);
		i++;
	}
	return 0;
}
