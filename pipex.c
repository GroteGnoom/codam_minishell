/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:43 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/17 12:58:53 by dnoom         ########   odam.nl         */
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

	pipex.term_out = dup(STDOUT_FILENO);
	pipex.term_in = dup(STDIN_FILENO);
	if (pipex.term_out < 0 || pipex.term_in < 0)
		perror("dup");
	pipex.len = nr_parts;
	pipex.size = ft_get_size_parts(parts);
	status = ft_pipex_pipe(pipex, s_env, parts);
	if (dup2(pipex.term_out, STDOUT_FILENO) < 0 || \
	dup2(pipex.term_in, STDIN_FILENO) < 0)
		perror("dup2");
	close(pipex.term_in);
	close(pipex.term_out);
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
	ft_free_strs(pipex.paths);
	return (status);
}

void	ft_check_here_doc(t_part *parts, t_pipe pipex)
{
	char	*line;
	int		i;

	i = ft_find_first_command(pipex, parts);
	while (parts[i].part && !is_pipe(parts[i]) && !isatty(pipex.term_in))
	{
		if (is_here_doc(parts[i]))
		{
			line = get_next_line(pipex.term_in);
			while (line && ft_strcmp(line, parts[i + 1].part))
			{
				free(line);
				line = get_next_line(pipex.term_in);
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
	int		pipefd[4];
	pid_t	child;

	while (pipex.iter < pipex.size)
	{
		if (pipe(pipefd + 2) < 0)
			perror("Pipe: ");
		child = fork();
		if (child < 0)
			perror("Fork: ");
		if (child == 0)
		{
			status = ft_child_process(pipex, pipefd, s_env, parts);
			exit(status);
		}
		if (pipex.iter > 0)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		waitpid(child, &status, 0);
		ft_check_here_doc(parts, pipex);
		pipefd[0] = pipefd[2];
		pipefd[1] = pipefd[3];
		pipex.iter++;
	}
	if (pipex.size > 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (WEXITSTATUS(status));
}
