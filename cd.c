/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:17:01 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/20 11:19:24 by dnoom         ########   odam.nl         */
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

static int	ft_absolute(char *path_str, char *cur_dir, \
t_part *parts, int line_nr);

static int	ft_relative(char *path_str, t_part *parts, int line_nr);

static int	ft_search_slash(char *cur_dir, int i);

int	ft_cd(t_part *parts, int line_nr, t_env *s_env)
{
	char	*home_dir;
	char	*cur_dir;
	int		err;

	err = 0;
	if (!parts[1].part)
	{
		home_dir = ft_search_name(s_env, "HOME", 4);
		if (!home_dir)
			return (ft_home_not_set(parts, 0, s_env->line_nr));
		if (chdir(home_dir) < 0)
			return (1);
	}
	else if (parts[1].part[0] == '/')
	{
		if (chdir(parts[1].part))
			return (ft_redir_error("cd", parts[1].part, line_nr));
		return (0);
	}
	else if (parts[1].part[0] == '.' && parts[1].part[1] == '.')
		return (ft_relative(parts[1].part, parts, line_nr));
	else
	{
		cur_dir = getcwd(NULL, PATH_MAX);
		err = ft_absolute(parts[1].part, cur_dir, parts, line_nr);
		free(cur_dir);
	}
	return (err);
}

static int	ft_absolute(char *path_str, char *cur_dir, \
t_part *parts, int line_nr)
{
	char	*home_dir;
	char	*new_dir;

	home_dir = ft_strjoin(cur_dir, "/");
	new_dir = ft_strjoin(home_dir, path_str);
	if (chdir(new_dir) < 0)
	{
		free(home_dir);
		free(new_dir);
		return (ft_redir_error("cd", parts[1].part, line_nr));
	}
	free(home_dir);
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
