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
	int		i;
	t_env	s_env;

	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	signals();
	copy_env(envp, &s_env);
	line = readline(PROMPT);
	last_exit_status = 0;
	i = 0;
	while (line)
	{
		if (ft_strlen(line))
			add_history(line);
		expand_args(&line, last_exit_status);
		args = ft_split(line, ' ');
		nr_args = count_strs(args);
		if (nr_args)
		{
			while (i < nr_args)
			{
				if (!ft_strcmp(args[i], "|"))
					last_exit_status = ft_pipex(nr_args, args, s_env.env);
				i++;
			}
			if (!ft_strcmp(args[0], "exit"))
				last_exit_status = ft_exit(args, nr_args);
			else if (!ft_strcmp(args[0], "echo"))
				last_exit_status = ft_echo(args, nr_args);
			else if (!ft_strcmp(args[0], "cd"))
				last_exit_status = ft_cd(args);
			else if (!ft_strcmp(args[0], "pwd"))
				last_exit_status = ft_pwd();
			else if (!ft_strcmp(args[0], "env"))
				last_exit_status = ft_env(s_env.env);
			else if (!ft_strcmp(args[0], "export"))
				last_exit_status = ft_export(args, &s_env);
			else if (!ft_strcmp(args[0], "unset"))
				last_exit_status = ft_unset(args, &s_env);
			else
				last_exit_status = ft_executable(args, &s_env);
		}
		free(line);
		line = readline(PROMPT);
	}
}
