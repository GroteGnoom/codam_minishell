/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:57:22 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/28 14:22:59 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	ft_multiple_redir(t_part *parts, char *str, int append, int line_nr);

static int	ft_get_args(t_part *new_args, t_part *parts, char *c)
{
	int	i;

	i = 0;
	while (ft_strcmp(parts->part, c) != 0)
	{
		new_args->part = ft_strdup(parts->part);
		parts++;
		new_args++;
		i++;
	}
	new_args = new_args - i;
	return (i);
}

int	redirect_in(int nr_parts, t_part *parts, t_env *s_env, int *exec, int line_nr)
{
	t_part	*new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	i = 0;
	*exec = 1;
	while (ft_strcmp(parts[i].part, "<") != 0)
		i++;
	fd = open(parts[i + 1].part, O_RDONLY);
	if (fd < 0)
		return (ft_redir_error(SHELL_NAME, parts[i + 1].part, line_nr));
	term = 1;
	if (dup2(STDIN_FILENO, term) < 0 || dup2(fd, STDIN_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	i = ft_get_args(new_args, parts, "<");
	ret = ft_executable(i, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDIN_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	return (ret);
}

int	redirect_out(int nr_parts, t_part *parts, t_env *s_env, int *exec, int line_nr)
{
	t_part	*new_args;
	int		ret;
	int		term;
	int		args;

	*exec = 1;
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	args = ft_get_args(new_args, parts, ">");
	term = 0;
	if (dup2(STDOUT_FILENO, term) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	ret = ft_multiple_redir(parts, ">", 0, line_nr);
	ret = ft_executable(args, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	return (ret);
}

int	redirect_out_app(int nr_parts, t_part *parts, t_env *s_env, int *exec, int line_nr)
{
	t_part	*new_args;
	int		ret;
	int		term;
	int		args;

	*exec = 1;
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	args = ft_get_args(new_args, parts, ">>");
	term = 0;
	if (dup2(STDOUT_FILENO, term) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	ret = ft_multiple_redir(parts, ">>", 1, line_nr);
	ret = ft_executable(args, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	return (ret);
}

static int	ft_multiple_redir(t_part *parts, char *str, int append, int line_nr)
{
	int	i;
	int	fd;

	i = 1;
	while (parts[i].part && ft_strcmp(parts[i].part, str) != 0)
			i++;
	if (append == 1)
		fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	while (parts[i + 1].part && parts[i + 2].part && \
	!ft_strcmp(parts[i + 2].part, str))
	{
		i++;
		while (parts[i].part && ft_strcmp(parts[i].part, str) != 0)
			i++;
		fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (ft_redir_error(SHELL_NAME, parts[i + 1].part, line_nr));
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (ft_redir_error("dup2", "", line_nr));
	}
	return (0);
}
