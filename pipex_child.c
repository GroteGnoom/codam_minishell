/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_child.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:26 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/17 09:41:37 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static void		ft_dup2(int first, int second);

int	ft_child_process(t_pipe pipex, int *pipefd, t_env *s_env, t_part *parts)
{
	int	status;

	if (pipex.iter == 0)
		ft_dup2(STDIN_FILENO, pipefd[3]);
	else if (pipex.iter == pipex.size - 1)
		ft_dup2(pipefd[0], STDOUT_FILENO);
	else
		ft_dup2(pipefd[0], pipefd[3]);
	if (pipex.iter != 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	close(pipefd[2]);
	close(pipefd[3]);
	pipex.cmd_flag = ft_get_cmd_flag(parts, pipex, s_env, &status);
	if (status)
		exit(status);
	if (pipex.cmd_flag[0].part)
		status = is_built_in(pipex.cmd_flag[0].part, \
		count_parts(pipex.cmd_flag), pipex.cmd_flag, s_env);
	free(pipex.cmd_flag);
	return (status);
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

int	ft_find_first_command(t_pipe pipex, t_part *parts)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (j < pipex.iter)
	{
		if (is_pipe(parts[i]))
			j++;
		i++;
	}
	return (i);
}

t_part	*ft_get_cmd_flag(t_part *parts, t_pipe pipex, \
t_env *s_env, int *status)
{
	int		i;
	int		j;

	i = ft_find_first_command(pipex, parts);
	j = 0;
	*status = 0;
	while (parts[i + j].part && !is_pipe(parts[i + j]))
	{
		if (ft_is_redir(parts[i + j]))
		{
			*status = ft_do_redir(parts, s_env->line_nr, i + j, pipex);
			if (*status)
				return (NULL);
			j++;
		}
		j++;
	}
	return (get_commands_between_pipes(parts + i, pipex, s_env));
}
