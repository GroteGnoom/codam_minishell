/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:57:22 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/12 11:24:40 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	ft_set_fd(char *part, int fd, int line_nr);

int	ft_multiple_redir(t_part *parts, int i, int line_nr, t_pipe pipex)
{
	int	ret;

	ret = 0;
	while (parts[i].part && !ft_is_redir(parts[i]))
		i++;
	ret = ft_do_redir(parts, line_nr, i, pipex);
	i += 2;
	while (parts[i].part && !is_pipe(parts[i]))
	{
		if (parts[i].part && parts[i + 1].part && ft_is_redir(parts[i]))
		{
			ret = ft_do_redir(parts, line_nr, i, pipex);
			i++;
		}
		i++;
	}
	return (ret);
}

int	ft_do_redir(t_part *parts, int line_nr, int i, t_pipe pipex)
{
	int	fd;

	if (!parts[i + 1].part)
		return (ft_syntax_error(parts, 0, line_nr, "newline"));
	if (parts[i + 1].type == SPECIAL)
		return (ft_syntax_error(parts, 0, line_nr, parts[i + 1].part));
	if (!ft_strcmp(parts[i].part, "<<"))
		return (here_doc(parts[i + 1].part, line_nr, parts, pipex));
	if (!ft_strcmp(parts[i].part, "<"))
		fd = open(parts[i + 1].part, O_RDONLY);
	else if (!ft_strcmp(parts[i].part, ">"))
		fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_redir_error(SHELL_NAME, parts[i + 1].part, line_nr));
	return (ft_set_fd(parts[i].part, fd, line_nr));
}

static int	ft_set_fd(char *part, int fd, int line_nr)
{
	if (!ft_strcmp(part, "<"))
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			return (ft_redir_error("dup2", "", line_nr));
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (ft_redir_error("dup2", "", line_nr));
	}
	return (0);
}
