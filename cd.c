/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:17:01 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/28 14:48:49 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
# include <sys/syslimits.h>
#else
# include <linux/limits.h>
#endif

static int	ft_absolute(char *path_str, char *home_dir, \
t_part *parts, int line_nr);

static int	ft_relative(char *path_str, t_part *parts, int line_nr);

static int	ft_search_slash(char *cur_dir, int i);

int	ft_cd(t_part *parts, int line_nr)
{
	char	*home_dir;
	char	*buf;
	char	*cur_dir;
	char	*new_dir;

	home_dir = getenv("HOME");
	if (!parts[1].part)
	{
		if (chdir(home_dir) < 0)
			return (1);
		return (0);
	}
	else if (parts[1].part[0] == '/')
		return (ft_absolute(parts[1].part, home_dir, parts, line_nr));
	else if (parts[1].part[0] == '.' && parts[1].part[1] == '.')
		return (ft_relative(parts[1].part, parts, line_nr));
	else
	{
		buf = NULL;
		cur_dir = getcwd(buf, PATH_MAX);
		new_dir = ft_strjoin(cur_dir, "/");
		free(cur_dir);
		return (ft_absolute(parts[1].part, new_dir, parts, line_nr));
	}
	return (0);
}

static int	ft_absolute(char *path_str, char *home_dir, \
t_part *parts, int line_nr)
{
	char	*new_dir;

	new_dir = ft_strjoin(home_dir, path_str);
	free(home_dir);
	if (chdir(new_dir) < 0)
	{
		free(new_dir);
		return (ft_redir_error("cd", parts[1].part, line_nr));
	}
	free(new_dir);
	return (0);
}

static int	ft_relative(char *path_str, t_part *parts, int line_nr)
{
	char	*cur_dir;
	char	*buf;
	int		i;

	i = 0;
	buf = NULL;
	cur_dir = getcwd(buf, PATH_MAX);
	free(buf);
	while (cur_dir[i])
		i++;
	i = ft_search_slash(cur_dir, i);
	if (!ft_strnstr(path_str, "..", 2))
		ft_substr_free(&cur_dir, 0, i + 1);
	else
		ft_strjoin_free(&cur_dir, "/");
	if (ft_strlen(path_str) > 3 || !ft_strcmp(path_str, ".."))
		ft_strjoin_free(&cur_dir, path_str);
	if (chdir(cur_dir) < 0)
		return (ft_redir_error("cd", parts[1].part, line_nr));
	free(cur_dir);
	return (0);
}

static int	ft_search_slash(char *cur_dir, int i)
{
	while (i > 0)
	{
		if (cur_dir[i] == '/')
			return (i);
		i--;
	}
	return (0);
}
