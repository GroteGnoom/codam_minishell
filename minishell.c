#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"

#define PROMPT "> "

int	count_strs(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	int		nr_args;
	int		last_exit_status;
	t_env	s_env;

	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	signals();
	copy_env(envp, &s_env);
	line = readline(PROMPT);
	last_exit_status = 0;
	while (line)
	{
		if (ft_strlen(line))
			add_history(line);
		expand_args(&line);
		args = ft_split(line, ' ');
		nr_args = count_strs(args);
		if (nr_args)
		{
			if (!ft_strcmp(args[0], "exit"))
				last_exit_status = ft_exit(args, nr_args);
			if (!ft_strcmp(args[0], "echo"))
				last_exit_status = ft_echo(args, nr_args);
			if (!ft_strcmp(args[0], "cd"))
				last_exit_status = ft_cd(args);
			if (!ft_strcmp(args[0], "pwd"))
				last_exit_status = ft_pwd();
			if (!ft_strcmp(args[0], "env"))
				ft_env(s_env.env);
			if (!ft_strcmp(args[0], "export"))
				last_exit_status = ft_export(args, &s_env);
		}
		free(line);
		line = readline(PROMPT);
	}
}
