/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 11:50:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 11:50:58 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "get_next_line_bonus.h"

int	add_to_line(char *src, size_t len, t_line *line)
{
	size_t	new_line_cap;

	if (!line->data)
	{
		line->cap = len;
		line->data = malloc(line->cap);
		line->len = 0;
	}
	else if (line->cap < line->len + len)
	{
		new_line_cap = (line->cap * 2) + len;
		line->data = ft_realloc(line->data, new_line_cap, line->cap);
		line->cap = new_line_cap;
	}
	if (!line->data)
		return (ERROR);
	ft_memcpy(line->data + line->len, src, len);
	line->len += len;
	return (SUCCESS);
}

int	read_into_buffer(t_buffer *buffer, int fd, t_line *line)
{
	if (buffer->pos != buffer->len)
		return (BUFFER_READ_OK);
	buffer->len = read(fd, buffer, BUFFER_SIZE);
	if (buffer->len == -1)
	{
		buffer->len = 0;
		if (line->data)
			free(line->data);
		line->data = NULL;
	}
	buffer->pos = 0;
	if (buffer->len == -1
		|| (!buffer->len && !line->data))
		return (NO_BUFFER_READ);
	if (!buffer->len)
	{
		add_to_line("", 1, line);
		return (NO_BUFFER_READ);
	}
	return (BUFFER_READ_OK);
}

char	*found_line(t_buffer *buffer, size_t length, t_line *line)
{
	add_to_line(buffer->data + buffer->pos,
		length + 1 - buffer->pos, line);
	if (!line->data)
		return (NULL);
	add_to_line("", 1, line);
	buffer->pos = length + 1;
	return (line->data);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffers[OPEN_MAX + 1] = {{{0}, 0, 0}};
	ssize_t			i;
	t_buffer		*buffer;
	t_line			line;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	buffer = &buffers[fd];
	line.data = NULL;
	while (1)
	{
		if (read_into_buffer(buffer, fd, &line) != BUFFER_READ_OK)
			return (line.data);
		i = buffer->pos;
		while (i < buffer->len)
		{
			if (buffer->data[i] == '\n')
				return (found_line(buffer, i, &line));
			i++;
		}
		add_to_line(buffer->data + buffer->pos, i - buffer->pos, &line);
		if (!line.data)
			return (NULL);
		buffer->pos = i;
	}
}
