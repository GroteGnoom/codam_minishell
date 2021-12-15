/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:10 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/14 10:38:39 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"
#include "get_next_line/get_next_line.h"

#define PROMPT "> "

int	count_parts(t_part *s)
{
	int	i;

	i = 0;
	while (s[i].part)
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
	int		comm;
	t_env	s_env;
	t_part	*parts;
	int		nr_parts;

	(void)argc;
	(void)argv;
	setbuf(stdout, NULL);
	signals();
	copy_env(envp, &s_env);
	if (isatty(STDIN_FILENO))
		line = readline(PROMPT);
	else
		line = get_next_line(STDIN_FILENO);
	last_exit_status = 0;
	comm = 0;
	while (line)
	{
		if (isatty(STDIN_FILENO) && ft_strlen(line))
			add_history(line);
		parts = quote_split(line);
		expand_unquoted_args(parts, last_exit_status);
		args = parts_to_strings(parts);
		ft_free_parts(parts);
		nr_args = ft_count_strs(args);
		parts = ft_shell_split(line);
		nr_parts = count_parts(parts);
		if (nr_args)
		{
			if (comm == 0)
			{
				i = 0;
				while (i < nr_parts)
				{
					if (parts[i].type == SPECIAL)
					{
						if (!ft_strcmp(parts[i].part, "|"))
						{
							last_exit_status = ft_pipex(nr_parts, parts, s_env.env);
							comm = 1;
							break ;
						}
						if (!ft_strcmp(parts[i].part, "<"))
						{
							last_exit_status = redirect_in(nr_parts, parts, &s_env);
							comm = 1;
							break ;
						}
						if (!ft_strcmp(parts[i].part, ">"))
						{
							last_exit_status = redirect_out(nr_parts, parts, &s_env);
							comm = 1;
							break ;
						}
						if (!ft_strcmp(parts[i].part, ">>"))
						{
							last_exit_status = redirect_out_app(nr_parts, parts, &s_env);
							comm = 1;
							break ;
						}
						if (!ft_strcmp(parts[i].part, "<<"))
						{
							last_exit_status = redirect_here_doc(nr_parts, parts, &s_env);
							comm = 1;
							break ;
						}
					}
					i++;
				}
			}
			if (comm == 0)
			{
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
					last_exit_status = ft_executable(nr_parts, parts, &s_env);
			}
			comm = 0;
		}
		free(line);
		ft_free_parts(parts);
		ft_free_strs(args);
		if (isatty(STDIN_FILENO))
			line = readline(PROMPT);
		else
			line = get_next_line(STDIN_FILENO);
	}
}
