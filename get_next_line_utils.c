/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 17:45:29 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/13 17:46:53 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

ssize_t		ft_min(ssize_t a, ssize_t b)
{
	return (a < b ? a : b);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
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
