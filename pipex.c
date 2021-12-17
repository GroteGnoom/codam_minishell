/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:43 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/17 13:48:50 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static int		ft_pipex_pipe(t_pipe pipe, t_env *s_env, t_part *parts);

static int		ft_get_size_parts(t_part *parts);

static int		ft_open_error(t_pipe pipex, int term_out, \
t_part *parts, int nr_parts);

static int		ft_execute_pipes(t_pipe pipex, t_env *s_env, \
t_part *parts, int *pipefd);

int	ft_pipex(int nr_parts, t_part *parts, t_env *s_env)
{
	t_pipe	pipex;
	int		status;
	int		term_out;
	int		term_in;

	pipex.begin = 0;
	pipex.end = 0;
	term_out = 3;
	term_in = 4;
	if (dup2(STDOUT_FILENO, term_out) < 0 || dup2(STDIN_FILENO, term_in) < 0)
		perror("dup2");
	pipex = ft_set_io(nr_parts, parts, pipex);
	if (pipex.infile < 0 || pipex.outfile < 0)
		return (ft_open_error(pipex, term_out, parts, nr_parts));
	pipex.commands = ft_get_commands_parts(nr_parts, parts, &pipex);
	pipex.size = ft_get_size_parts(parts);
	status = ft_pipex_pipe(pipex, s_env, parts);
	close(pipex.infile);
	close(pipex.outfile);
	if (dup2(term_out, STDOUT_FILENO) < 0 || dup2(term_in, STDIN_FILENO) < 0)
		perror("dup2");
	close(term_in);
	close(term_out);
	ft_free_strs(pipex.commands);
	return (status);
}

static int	ft_open_error(t_pipe pipex, int term_out, \
t_part *parts, int nr_parts)
{
	write(term_out, "minishell: ", 11);
	if (pipex.infile < 0)
		write(1, parts[1].part, ft_strlen(parts[1].part));
	else
		write(1, parts[nr_parts - 1].part, ft_strlen(parts[1].part));
	write(1, ": No such file or directory\n", 28);
	if (pipex.outfile < 0)
		return (127);
	return (0);
}

static int	ft_get_size_parts(t_part *parts)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (parts[i].part)
	{
		if (parts[i].type == SPECIAL && !ft_strcmp(parts[i].part, "|"))
			count++;
		i++;
	}
	return (count);
}

static int	ft_pipex_pipe(t_pipe pipex, t_env *s_env, t_part *parts)
{
	int		*pipefd;
	int		status;

	pipefd = (int *)malloc((2 * (pipex.size)) * sizeof(int));
	if (!pipefd)
		perror("malloc: ");
	pipex = ft_get_pipes(pipex, pipefd);
	pipex.paths = ft_get_paths(s_env->env);
	pipex.iter = 0;
	status = ft_execute_pipes(pipex, s_env, parts, pipefd);
	ft_free_strs(pipex.paths);
	return (WEXITSTATUS(status));
}

static int	ft_execute_pipes(t_pipe pipex, t_env *s_env, \
t_part *parts, int *pipefd)
{
	pid_t	child;
	int		status;

	while (pipex.iter < pipex.size)
	{
		child = fork();
		if (child < 0)
			perror("Fork: ");
		if (child == 0)
			ft_child_process(pipex, pipefd, s_env, parts);
		pipex.iter++;
	}
	ft_close_all_pipes(pipex, pipefd);
	while (pipex.iter > 0)
	{
		waitpid(-1, &status, 0);
		pipex.iter--;
	}
	waitpid(child, &status, 0);
	return (status);
}
