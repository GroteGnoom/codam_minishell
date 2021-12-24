/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_child.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:26 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/17 11:20:07 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static void	ft_dup2(int first, int second);

static char	**ft_get_cmd_flag(char **commands, int iter, t_pipe pipex);

void	ft_child_process(t_pipe pipex, int *pipefd, t_env *s_env, t_part *parts)
{
	if (pipex.iter == 0)
		ft_dup2(pipex.infile, pipefd[1]);
	else if (pipex.iter == pipex.size - 1)
		ft_dup2(pipefd[2 * pipex.iter - 2], pipex.outfile);
	else
		ft_dup2(pipefd[2 * pipex.iter - 2], pipefd[2 * pipex.iter + 1]);
	ft_close_all_pipes(pipex, pipefd);
	pipex.cmd_flag = ft_get_cmd_flag(pipex.commands, pipex.iter, pipex);
	ft_try_paths(pipex.paths, pipex.cmd_flag, s_env, parts);
}

static void	ft_dup2(int first, int second)
{
	if (dup2(first, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(errno);
	}
	if (dup2(second, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(errno);
	}
}

static char	**ft_get_cmd_flag(char **commands, int iter, t_pipe pipex)
{
	char	**cmd;
	int		pipes;
	int		i;
	int		j;

	pipes = 0;
	i = pipex.begin;
	j = 0;
	cmd = ft_calloc((pipex.len + 1) * sizeof(char *), 1);
	while (pipes < iter)
	{
		if (!ft_strcmp(commands[i], "|"))
			pipes++;
		i++;
	}
	if (pipex.begin)
		pipex.len -= pipex.end;
	while (commands[i] && i < pipex.len && ft_strcmp(commands[i], "|"))
		cmd[j++] = ft_strdup(commands[i++]);
	if (i == pipex.len + pipex.end)
		free(commands[i]);
	return (cmd);
}
