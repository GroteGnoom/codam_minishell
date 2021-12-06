#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "Libft/libft.h"

#define PROMPT "> "

int	main(void)
{
	char	*line;

	line = readline(PROMPT);
	while (line)
	{
		if (ft_strlen(line))
			add_history(line);
		free(line);
		line = readline(PROMPT);
	}
}
