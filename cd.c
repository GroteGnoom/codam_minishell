/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:17:01 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 11:33:18 by sde-rijk      ########   odam.nl         */
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

static char	*ft_set_pwds(char *old_dir);

int	ft_cd(t_part *parts, int line_nr, t_env *s_env)
{
	char	*home_dir;
	char	*old_dir;
	char	*cur_dir;
	int		err;

	err = 0;
	old_dir = getcwd(NULL, PATH_MAX);
	if (!parts[1].part)
	{
		home_dir = ft_search_name(s_env, "HOME", 4);
		if (!home_dir)
			err = ft_home_not_set(parts, 0, s_env->line_nr);
		if (chdir(home_dir) < 0)
			err = 1;
	}
	else if (parts[1].part[0] == '/')
	{
		if (chdir(parts[1].part))
			err = ft_redir_error("cd", parts[1].part, line_nr);
	}
	else if (parts[1].part[0] == '.' && parts[1].part[1] == '.')
		err = ft_relative(parts[1].part, parts, line_nr);
	else
	{
		cur_dir = getcwd(NULL, PATH_MAX);
		err = ft_absolute(parts[1].part, cur_dir, parts, line_nr);
		free(cur_dir);
	}
	if (err == 0)
		old_dir = ft_set_pwds(old_dir);
	free(old_dir);
	return (err);
}

static char	*ft_set_pwds(char *old_dir)
{
	char	*old_dir_env;
	char	*cur_dir;
	char	*cur_dir_env;

	old_dir_env = ft_strjoin("OLDPWD=", old_dir);
	ft_export_var(s_env, old_dir_env, ft_strdup("OLDPWD"));
	free(old_dir_env);
	free(old_dir);
	cur_dir = getcwd(NULL, PATH_MAX);
	cur_dir_env = ft_strjoin("PWD=", cur_dir);
	ft_export_var(s_env, cur_dir_env, ft_strdup("PWD"));
	free(cur_dir_env);
	return (cur_dir);
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
