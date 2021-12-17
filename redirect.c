/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:57:22 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/17 11:44:31 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static int	ft_redir_error(char *str)
{
	perror(str);
	return (1);
}

int	redirect_in(int nr_parts, t_part *parts, t_env *s_env)
{
	t_part	*new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	fd = open(parts[nr_parts - 1].part, O_RDONLY);
	if (fd < 0)
		return (ft_redir_error("bash"));
	term = 1;
	if (dup2(STDIN_FILENO, term) < 0 || dup2(fd, STDIN_FILENO) < 0)
		return (ft_redir_error("dup2"));
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	i = 0;
	while (ft_strcmp(parts->part, "<") != 0)
	{
		new_args->part = ft_strdup(parts->part);
		parts++;
		new_args++;
		i++;
	}
	new_args = new_args - i;
	ret = ft_executable(i, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDIN_FILENO) < 0)
		return (ft_redir_error("dup2"));
	return (ret);
}

int	redirect_out(int nr_parts, t_part *parts, t_env *s_env)
{
	t_part	*new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	fd = open(parts[nr_parts - 1].part, O_RDWR | O_CREAT | O_TRUNC, 0644);
	term = 0;
	if (dup2(STDOUT_FILENO, term) < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2"));
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	i = 0;
	while (ft_strcmp(parts->part, ">") != 0)
	{
		new_args->part = ft_strdup(parts->part);
		parts++;
		new_args++;
		i++;
	}
	new_args = new_args - i;
	ret = ft_executable(i, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2"));
	return (ret);
}

int	redirect_out_app(int nr_parts, t_part *parts, t_env *s_env)
{
	t_part	*new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	fd = open(parts[nr_parts - 1].part, O_RDWR | O_CREAT | O_APPEND, 0644);
	term = 0;
	if (dup2(STDOUT_FILENO, term) < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2"));
	new_args = ft_calloc((nr_parts - 1) * sizeof(*parts), 1);
	i = 0;
	while (ft_strcmp(parts->part, ">>") != 0)
	{
		new_args->part = ft_strdup(parts->part);
		parts++;
		new_args++;
		i++;
	}
	new_args = new_args - i;
	ret = ft_executable(i, new_args, s_env);
	ft_free_parts(new_args);
	if (dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2"));
	return (ret);
}

int	redirect_here_doc(int nr_parts, t_part *parts, t_env *s_env)
{
	t_part	*new_args;
	char	*final;
	pid_t	child;
	int		status;
	int		i;

	i = 0;
	new_args = ft_calloc((nr_parts) * sizeof(*parts), 1);
	while (ft_strcmp(parts[i].part, "<<") != 0)
	{
		new_args[i].part = ft_strdup(parts[i].part);
		i++;
	}
	final = ft_strdup(parts[i + 1].part);
	child = fork();
	if (child < 0)
		perror("Fork: ");
	if (child == 0)
		here_doc(final, i, new_args, s_env);
	waitpid(-1, &status, 0);
	ft_free_parts(new_args);
	free(final);
	return (0);
}
