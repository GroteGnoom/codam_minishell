/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:57:22 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/07 11:39:28 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	ft_multiple_redir(t_part *parts, int line_nr);

static int	ft_get_args(t_part *new_args, t_part *parts)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (parts[i].part)
	{
		if (ft_is_redir(parts[i]))
		{
			if (!parts[i + 1].part || !parts[i + 2].part)
				break ;
			i += 2;
			continue ;
		}
		new_args[j].part = ft_strdup(parts[i].part);
		i++;
		j++;
		count++;
	}
	return (count);
}

int	ft_redirections(int nr_parts, t_part *parts, t_env *s_env, int *exec)
{
	t_part	*new_args;
	int		ret;
	int		term_in;
	int		term_out;
	int		args;

	*exec = 1;
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	args = ft_get_args(new_args, parts);
	term_in = dup(STDIN_FILENO);
	term_out = dup(STDOUT_FILENO);
	if (term_in < 0 || term_out < 0)
		return (ft_redir_error("dup", "", s_env->line_nr));
	ret = ft_multiple_redir(parts, s_env->line_nr);
	if (!ret)
		ret = ft_executable(args, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term_in, STDIN_FILENO) < 0 || dup2(term_out, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", "", s_env->line_nr));
	return (ret);
}

static int	ft_multiple_redir(t_part *parts, int line_nr)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (parts[i].part && !ft_is_redir(parts[i]))
		i++;
	ret = ft_do_redir(parts, line_nr, i);
	i += 2;
	while (parts[i].part)
	{
		if (parts[i].part && parts[i + 1].part && ft_is_redir(parts[i]))
		{
			ret = ft_do_redir(parts, line_nr, i);
			i++;
		}
		i++;
	}
	return (ret);
}

int	ft_do_redir(t_part *parts, int line_nr, int i)
{
	int	fd;

	if (!parts[i + 1].part)
		return (ft_syntax_error(parts, 0, line_nr, "newline"));
	if (parts[i + 1].type == SPECIAL)
		return (ft_syntax_error(parts, 0, line_nr, parts[i + 1].part));
	if (!ft_strcmp(parts[i].part, "<"))
		fd = open(parts[i + 1].part, O_RDONLY);
	else if (!ft_strcmp(parts[i].part, ">"))
		fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_redir_error(SHELL_NAME, parts[i + 1].part, line_nr));
	if (!ft_strcmp(parts[i].part, "<"))
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
