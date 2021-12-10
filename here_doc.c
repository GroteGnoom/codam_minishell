#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
char	**here_doc(char *final)
{
	char	**args;
	char	*line;
	int		size;

	size = 2;
	line = readline("here_doc> ");
	args = NULL;
	while (line)
	{
		if (!ft_strcmp(line, final))
			return (args);
		args = ft_realloc(args, size * sizeof(char *), \
		size - 1 * sizeof(char *));
		args[size - 1] = NULL;
		args[size - 2] = ft_strdup(line);
		printf("%s\n\n", args[size - 2]);
		free(line);
		line = readline("here_doc> ");
		size++;
	}
	return (0);
}
