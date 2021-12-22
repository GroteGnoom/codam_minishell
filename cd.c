/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:17:01 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/15 16:40:56 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*#include <sys/syslimits.h>*/
#include <linux/limits.h>


static int	ft_absolute(char *path_str, char *home_dir);

static int	ft_relative(char *path_str);

static int	ft_search_slash(char *cur_dir, int i);

int	ft_cd(t_part *parts)
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
		return (ft_absolute(parts[1].part, home_dir));
	else if (parts[1].part[0] == '.' && parts[1].part[1] == '.')
		return (ft_relative(parts[1].part));
	else
	{
		buf = NULL;
		cur_dir = getcwd(buf, PATH_MAX);
		new_dir = ft_strjoin(cur_dir, "/");
		free(cur_dir);
		return (ft_absolute(parts[1].part, new_dir));
	}
	return (0);
}

static int	ft_absolute(char *path_str, char *home_dir)
{
	char	*new_dir;

	new_dir = ft_strjoin(home_dir, path_str);
	if (chdir(new_dir) < 0)
		return (1);
	free(home_dir);
	free(new_dir);
	return (0);
}

static int	ft_relative(char *path_str)
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
	ft_substr_free(&cur_dir, 0, i + 1);
	if (ft_strlen(path_str) > 3)
	{
		ft_substr_free(&path_str, 3, ft_strlen(path_str));
		ft_strjoin_free(&cur_dir, path_str);
	}
	if (chdir(cur_dir) < 0)
		return (1);
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
