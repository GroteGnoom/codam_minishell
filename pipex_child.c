/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_child.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:26 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/06 15:38:29 by daniel        ########   odam.nl         */
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
t_env *s_env, char **commands);

static void	ft_check_filename(char **str, t_env *s_env, t_part *parts, int i);

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
	pipex.cmd_flag = ft_get_cmd_flag(parts, pipex, s_env, pipex.commands);
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
t_env *s_env, char **commands)
{
	int		i;

	i = ft_find_first_command(pipex, parts);
	if (pipex.begin)
		pipex.len -= pipex.end;
	if (ft_is_redir(parts[i]))
		ft_check_filename(commands + i, s_env, parts, i);
	return (get_commands_between_pipes(parts + i, pipex, s_env, commands + i));
}

static void	ft_check_filename(char **str, t_env *s_env, t_part *parts, int i)
{
	int	fd;
	char	*filename;

	filename = parts[i + 1].part;
	if (!filename)
		ft_syntax_error(parts, 0, s_env->line_nr, "newline");
	else if (parts[i + 1].type == SPECIAL)
		ft_syntax_error(parts, 0, s_env->line_nr, filename);
	else
	{
		if (!ft_strcmp(str[0], "<"))
			fd = open(filename, O_RDONLY);
		else
			fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			ft_redir_error(SHELL_NAME, filename, s_env->line_nr);
		else
			close(fd);
	}
	exit(0);
}
