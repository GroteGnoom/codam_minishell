/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:10 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/11 11:46:17 by daniel        ########   odam.nl         */
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

int	check_for_pipes(int *exit_status, t_part *parts, \
t_env *s_env, int nr_parts)
{
	int	i;

	i = 0;
	while (i < nr_parts)
	{
		if (parts[i].type == SPECIAL && ft_strchr(parts[i].part, '|'))
		{
			if (!i || parts[i - 1].type == SPECIAL)
				*exit_status = ft_syntax_error(parts, i, s_env->line_nr, "|");
			else if (i == nr_parts - 1)
				*exit_status = ft_syntax_error_eof(s_env->line_nr);
			else if (ft_strcmp(parts[i].part, "|") \
		|| (parts[i + 1].type == SPECIAL && ft_strchr(parts[i + 1].part, '|')))
				*exit_status = ft_syntax_error(parts, i, s_env->line_nr, "|");
			else
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_parts(int *last_exit_status, char *line, t_env *s_env)
{
	t_part	*parts;
	int		nr_parts;
	int		syntax_error;

	parts = ft_shell_split(line, *last_exit_status, s_env);
	nr_parts = count_parts(parts);
	if (nr_parts)
	{
		syntax_error = check_for_pipes(last_exit_status, parts, \
		s_env, nr_parts);
		if (!syntax_error)
			*last_exit_status = ft_pipex(nr_parts, parts, s_env);
	}
	free(line);
	ft_free_parts(parts);
	return (*last_exit_status);
}

int	loop_through_lines(char *line, int last_exit_status, t_env *s_env)
{
	while (line)
	{
		if (isatty(STDIN_FILENO) && ft_strlen(line))
			add_history(line);
		last_exit_status = ft_check_parts(&last_exit_status, line, s_env);
		if (isatty(STDIN_FILENO))
			line = readline(PROMPT);
		else
			line = get_next_line(STDIN_FILENO);
		s_env->line_nr++;
	}
	return (last_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		last_exit_status;
	t_env	s_env;

	(void)argc;
	(void)argv;
	s_env.line_nr = 1;
	setbuf(stdout, NULL);
	signals();
	copy_env(envp, &s_env);
	if (isatty(STDIN_FILENO))
		line = readline(PROMPT);
	else
	{
		line = get_next_line(STDIN_FILENO);
		line = ft_strtrim_free(&line, "\n");
	}
	last_exit_status = 0;
	last_exit_status = loop_through_lines(line, last_exit_status, &s_env);
	ft_free_strs(s_env.env);
	return (last_exit_status);
}
