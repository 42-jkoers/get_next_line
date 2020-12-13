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
