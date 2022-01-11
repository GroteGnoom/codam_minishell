/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:43 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/11 13:38:36 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int		ft_pipex_pipe(t_pipe pipe, t_env *s_env, t_part *parts);

static int		ft_get_size_parts(t_part *parts);

static int		ft_execute_pipes(t_pipe pipex, t_env *s_env, \
t_part *parts, int *pipefd);

static int		ft_wait_for_child(t_pipe pipex, pid_t child);

int	ft_pipex(int nr_parts, t_part *parts, t_env *s_env)
{
	t_pipe	pipex;
	int		status;
	int		term_out;
	int		term_in;

	pipex.begin = 0;
	pipex.end = 0;
	term_out = dup(STDOUT_FILENO);
	term_in = dup(STDIN_FILENO);
	if (term_out < 0 || term_in < 0)
		perror("dup");
	pipex.len = nr_parts;
	pipex.size = ft_get_size_parts(parts);
	status = ft_pipex_pipe(pipex, s_env, parts);
	if (dup2(term_out, STDOUT_FILENO) < 0 || dup2(term_in, STDIN_FILENO) < 0)
		perror("dup2");
	close(term_in);
	close(term_out);
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
	int		pipefd[4];
	int		status;

	pipex.paths = ft_get_paths(s_env->env);
	pipex.iter = 0;
	status = ft_execute_pipes(pipex, s_env, parts, pipefd);
	ft_free_strs(pipex.paths);
	return (status);
}

static int	ft_execute_pipes(t_pipe pipex, t_env *s_env, \
t_part *parts, int *pipefd)
{
	pid_t	child;
	int		status;

	child = 0;
	if (pipex.size == 1)
	{
		pipex.cmd_flag = ft_get_cmd_flag(parts, pipex, s_env, &status);
		if (!status)
		{
			status = is_built_in(pipex.cmd_flag[0].part, count_parts(pipex.cmd_flag), pipex.cmd_flag, s_env);
			free(pipex.cmd_flag);
		}
		return (status);
	}
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
		pipefd[0] = pipefd[2];
		pipefd[1] = pipefd[3];
		pipex.iter++;
	}
	if (pipex.size > 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (ft_wait_for_child(pipex, child));
}

static int	ft_wait_for_child(t_pipe pipex, pid_t child)
{
	int	status;

	while (pipex.iter > 0)
	{
		waitpid(-1, &status, 0);
		pipex.iter--;
	}
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}
