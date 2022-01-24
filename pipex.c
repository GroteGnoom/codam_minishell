/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:43 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 14:11:37 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int		ft_pipex_pipe(t_pipe pipex, t_env *s_env, t_part *parts);

static int		ft_get_size_parts(t_part *parts);

static int		ft_execute_pipes(t_pipe pipex, t_part *parts, \
t_env *s_env, int status);

int	ft_pipex(int nr_parts, t_part *parts, t_env *s_env)
{
	t_pipe	pipex;
	int		status;

	pipex.len = nr_parts;
	pipex.size = ft_get_size_parts(parts);
	status = ft_pipex_pipe(pipex, s_env, parts);
	if (dup2(s_env->term_out, STDOUT_FILENO) < 0 || \
	dup2(s_env->term_in, STDIN_FILENO) < 0)
		perror("dup2");
	return (status);
}

static int	ft_get_size_parts(t_part *parts)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (parts[i].part)
	{
		if (is_pipe(parts[i]) == 1)
			count++;
		i++;
	}
	return (count);
}

static int	ft_pipex_pipe(t_pipe pipex, t_env *s_env, t_part *parts)
{
	int		status;

	pipex.paths = ft_get_paths(s_env->env);
	pipex.iter = 0;
	status = 0;
	if (pipex.size == 1)
	{
		pipex.cmd_flag = ft_get_cmd_flag(parts, pipex, s_env, &status);
		if (!status)
		{
			if (count_parts(pipex.cmd_flag))
			{
				status = is_built_in(pipex.cmd_flag[0].part, \
					count_parts(pipex.cmd_flag), pipex.cmd_flag, s_env);
			}
			free(pipex.cmd_flag);
		}
	}
	else
		status = ft_execute_pipes(pipex, parts, s_env, status);
	ft_free_ptr_array((void **)pipex.paths);
	return (status);
}

void	ft_check_here_doc(t_part *parts, t_pipe pipex, t_env *s_env)
{
	char	*line;
	int		i;

	i = ft_find_first_command(pipex, parts);
	while (parts[i].part && !is_pipe(parts[i]) && !isatty(s_env->term_in))
	{
		if (is_here_doc(parts[i]))
		{
			line = get_next_line(s_env->term_in);
			line = ft_strtrim_free(&line, "\n");
			while (line && ft_strcmp(line, parts[i + 1].part))
			{
				free(line);
				line = get_next_line(s_env->term_in);
				line = ft_strtrim_free(&line, "\n");
			}
			if (line)
				free(line);
			return ;
		}
		i++;
	}
}

static int	ft_execute_pipes(t_pipe pipex, t_part *parts, \
t_env *s_env, int status)
{
	pid_t	*child;

	child = ft_calloc(pipex.size + 1, sizeof(*child));
	while (pipex.iter < pipex.size)
	{
		if (pipe(pipex.pipefd + 2) < 0)
			perror("Pipe: ");
		child[pipex.iter] = ft_do_forks(pipex, parts, s_env, status);
		ft_check_here_doc(parts, pipex, s_env);
		pipex.pipefd[0] = pipex.pipefd[2];
		pipex.pipefd[1] = pipex.pipefd[3];
		pipex.iter++;
	}
	while (0 < pipex.iter)
	{
		waitpid(child[pipex.iter], &status, 0);
		pipex.iter--;
	}
	free(child);
	if (pipex.size > 1)
	{
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
	}
	return (WEXITSTATUS(status));
}
