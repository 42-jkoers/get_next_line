/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 20:21:28 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/14 20:22:18 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	
#include <stdio.h>
#include <fcntl.h>

int		main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	i = 0;
	setvbuf(stdout, NULL, _IONBF, 0);
	while (get_next_line(fd, &line) >= 0 && i < 10)
	{
		printf("<%s>\n", line);
		free(line);
		i++;
	}
	// while (1);
	return 0;
}
