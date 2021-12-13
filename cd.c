/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:17:01 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:17:03 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syslimits.h>

static int	ft_absolute(char *path_str, char *home_dir);

static int	ft_relative(char *path_str);

int	ft_cd(char **args)
{
	char	*home_dir;
	char	*buf;
	char	*cur_dir;
	char	*new_dir;

	home_dir = getenv("HOME");
	buf = NULL;
	if (!args[1])
	{
		if (chdir(home_dir) < 0)
			return (1);
		return (0);
	}
	else if (args[1][0] == '/')
		return (ft_absolute(args[1], home_dir));
	else if (args[1][0] == '.' && args[1][1] == '.')
		return (ft_relative(args[1]));
	else
	{
		cur_dir = getcwd(buf, PATH_MAX);
		new_dir = ft_strjoin(cur_dir, "/");
		return (ft_absolute(args[1], new_dir));
	}
	return (0);
}

static int	ft_absolute(char *path_str, char *home_dir)
{
	char	*new_dir;

	new_dir = ft_strjoin(home_dir, path_str);
	if (chdir(new_dir) < 0)
		return (1);
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
	while (i > 0)
	{
		if (cur_dir[i] == '/')
			break ;
		i--;
	}
	ft_substr_free(&cur_dir, 0, i + 1);
	if (ft_strlen(path_str) > 3)
	{
		ft_substr_free(&path_str, 3, ft_strlen(path_str));
		ft_strjoin_free(&cur_dir, path_str);
	}
	if (chdir(cur_dir) < 0)
		return (1);
	return (0);
}
