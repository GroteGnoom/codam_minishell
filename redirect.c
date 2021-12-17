/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:57:22 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/17 14:51:48 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	ft_redir_error(char *str, char *str2)
{
	if (!str2)
		perror(str);
	else
	{
		write(1, str, ft_strlen(str));
		write(1, ": ", 2);
		write(1, str2, ft_strlen(str2));
		write(1, ": No such file or directory\n", 28);
	}
	return (1);
}

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

int	redirect_in(int nr_parts, t_part *parts, t_env *s_env, int *exec)
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
		return (ft_redir_error("minishell", parts[i + 1].part));
	term = 1;
	if (dup2(STDIN_FILENO, term) < 0 || dup2(fd, STDIN_FILENO) < 0)
		return (ft_redir_error("dup2", ""));
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	i = ft_get_args(new_args, parts, "<");
	ret = ft_executable(i, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDIN_FILENO) < 0)
		return (ft_redir_error("dup2", ""));
	return (ret);
}

int	redirect_out(int nr_parts, t_part *parts, t_env *s_env, int *exec)
{
	t_part	*new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	i = 0;
	*exec = 1;
	while (ft_strcmp(parts[i].part, ">") != 0)
		i++;
	fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_redir_error("minishell", parts[i + 1].part));
	term = 0;
	if (dup2(STDOUT_FILENO, term) < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", ""));
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	i = ft_get_args(new_args, parts, ">");
	ret = ft_executable(i, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", ""));
	return (ret);
}

int	redirect_out_app(int nr_parts, t_part *parts, t_env *s_env, int *exec)
{
	t_part	*new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	i = 0;
	*exec = 1;
	while (ft_strcmp(parts[i].part, ">>") != 0)
		i++;
	fd = open(parts[i + 1].part, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_redir_error("minishell", parts[i + 1].part));
	term = 0;
	if (dup2(STDOUT_FILENO, term) < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", ""));
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	i = ft_get_args(new_args, parts, ">>");
	ret = ft_executable(i, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", ""));
	return (ret);
}
