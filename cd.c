/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:17:01 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 13:04:16 by sde-rijk      ########   odam.nl         */
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

static int	ft_relative(char *path_str, char *cur_dir, \
t_part *parts, int line_nr);

static void	ft_set_pwds(char *old_dir, t_env *s_env);

static int	ft_cd_home(t_env *s_env, t_part *parts);

static int	ft_cd_oldpwd(t_env *s_env, t_part *parts);

int	ft_cd(t_part *parts, int line_nr, t_env *s_env)
{
	char	*old_dir;
	int		err;
	char	buf[PATH_MAX];

	err = 0;
	old_dir = getcwd(buf, PATH_MAX);
	if (!parts[1].part)
		err = ft_cd_home(s_env, parts);
	else if (parts[1].part == '-')
		err = ft_cd_oldpwd(s_env, parts);
	else if (parts[1].part[0] == '/')
	{
		if (chdir(parts[1].part))
			err = ft_redir_error("cd", parts[1].part, line_nr);
	}
	else
		err = ft_relative(parts[1].part, old_dir, parts, line_nr);
	if (err == 0)
		ft_set_pwds(old_dir, s_env);
	return (err);
}

static int	ft_cd_oldpwd(t_env *s_env, t_part *parts)
{
	char	*old_pwd;

	old_pwd = ft_search_name(s_env, "OLDPWD", 7);
	if (!old_pwd)
		return (ft_home_not_set(parts, 0, s_env->line_nr, "OLDPWD"));
	if (chdir(old_pwd) < 0)
		return (1);
	return (0);
}

static int	ft_cd_home(t_env *s_env, t_part *parts)
{
	char	*home_dir;

	home_dir = ft_search_name(s_env, "HOME", 4);
	if (!home_dir)
		return (ft_home_not_set(parts, 0, s_env->line_nr, "HOME"));
	if (chdir(home_dir) < 0)
		return (1);
	return (0);
}

static void	ft_set_pwds(char *old_dir, t_env *s_env)
{
	char	*old_dir_env;
	char	*cur_dir;
	char	*cur_dir_env;
	char	buf[PATH_MAX];

	old_dir_env = ft_strjoin("OLDPWD=", old_dir);
	ft_export_var(s_env, old_dir_env, "OLDPWD");
	free(old_dir_env);
	cur_dir = getcwd(buf, PATH_MAX);
	cur_dir_env = ft_strjoin("PWD=", cur_dir);
	ft_export_var(s_env, cur_dir_env, "PWD");
	free(cur_dir_env);
}

static int	ft_relative(char *path_str, char *cur_dir, \
t_part *parts, int line_nr)
{
	char	*home_dir;
	char	*new_dir;
	int		err;

	err = 0;
	home_dir = ft_strjoin(cur_dir, "/");
	new_dir = ft_strjoin(home_dir, path_str);
	if (chdir(new_dir) < 0)
		err = ft_redir_error("cd", parts[1].part, line_nr);
	free(home_dir);
	free(new_dir);
	return (err);
}
