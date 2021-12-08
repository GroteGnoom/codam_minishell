#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"

#define PROMPT "> "

int	is_int(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	count_strs(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	handle_exit(char **args, int nr_args)
{
	if (nr_args == 1)
		exit(0);
	if (!is_int(args[1]))
	{
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}
	if (nr_args > 2)
		printf("minishell: exit: too many arguments\n");
	else
		exit(ft_atoi(args[1]));
}

int	main(void)
{
	char	*line;
	char	**args;
	int		nr_args;

	signals();
	line = readline(PROMPT);
	while (line)
	{
		if (ft_strlen(line))
			add_history(line);
		args = ft_split(line, ' ');
		nr_args = count_strs(args);
		if (nr_args)
		{
			if (!ft_strcmp(args[0], "exit"))
				handle_exit(args, nr_args);
		}
		free(line);
		line = readline(PROMPT);
	}
}
