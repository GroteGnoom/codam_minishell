/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_child.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:26 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/07 11:27:17 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static void	ft_dup2(int first, int second);

static char	**ft_get_cmd_flag(t_part *parts, t_pipe pipex, \
t_env *s_env);

static void	ft_check_filename(t_env *s_env, t_part *parts, int i);

void	ft_child_process(t_pipe pipex, int *pipefd, t_env *s_env, t_part *parts)
{
	if (pipex.iter == 0)
		ft_dup2(pipex.infile, pipefd[3]);
	else if (pipex.iter == pipex.size - 1)
		ft_dup2(pipefd[0], pipex.outfile);
	else
		ft_dup2(pipefd[0], pipefd[3]);
	if (pipex.iter != 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	close(pipefd[2]);
	close(pipefd[3]);
	pipex.cmd_flag = ft_get_cmd_flag(parts, pipex, s_env);
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

static char	**ft_get_cmd_flag(t_part *parts, t_pipe pipex, \
t_env *s_env)
{
	int		i;

	i = ft_find_first_command(pipex, parts);
	if (pipex.begin)
		pipex.len -= pipex.end;
	if (ft_is_redir(parts[i]))
		ft_check_filename(s_env, parts, i);
	return (get_commands_between_pipes(parts + i, pipex, s_env));
}

static void	ft_check_filename(t_env *s_env, t_part *parts, int i)
{
	char	*filename;
	int		ret;

	filename = parts[i + 1].part;
	if (!filename)
	{
		ft_syntax_error(parts, 0, s_env->line_nr, "newline");
		exit(0);
	}
	else if (parts[i + 1].type == SPECIAL)
	{
		ft_syntax_error(parts, 0, s_env->line_nr, filename);
		exit(0);
	}
	else
		ret = ft_do_redir(parts, s_env->line_nr, i);
	if (ret == 1)
		exit(0);
}
