#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <unistd.h>

# define NO_BUFFER_READ 1
# define BUFFER_READ_OK 0
# define ERROR 1
# define SUCCESS 0

typedef struct s_line
{
	char	*data;
	size_t	cap;
	size_t	len;
}	t_line;

typedef struct s_buffer {
	char	data[BUFFER_SIZE];
	ssize_t	pos;
	ssize_t	len;
}	t_buffer;

void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*cleanup(char **line);
int		read_into_buffer(t_buffer *gnl, int fd, t_line *line);
int		add_to_line(char *buffer, size_t len, t_line *line);
char	*new_line(t_line *line);
char	*found_line(t_buffer *gnl, size_t length, t_line *line);
void	*ft_realloc(void *p, size_t size, size_t old_size);

#endif
