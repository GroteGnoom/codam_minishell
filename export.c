/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:23 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/15 13:52:00 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <termios.h>
#include <stdio.h>

static int	export_attribute(t_env *s_env, char *attr);

static void	ft_free(t_env *s_env);

int	ft_export(t_part *parts, t_env *s_env)
{
	char	*env;
	char	*env_str;
	int		i;

	if (!parts[1].part || parts[1].type != NORMAL)
		return (ft_export_print(s_env->env));
	env_str = NULL;
	i = 0;
	env = ft_strchr(parts[1].part, '=');
	if (env != 0)
		env = ft_substr(parts[1].part, 0, ft_strlen(parts[1].part) \
		- ft_strlen(env));
	else
		return (export_attribute(s_env, parts[1].part));
	while (i < s_env->size && !env_str)
	{
		env_str = ft_strnstr(s_env->env[i], env, ft_strlen(s_env->env[i]));
		i++;
	}
	if (i == s_env->size)
		return (export_attribute(s_env, parts[1].part));
	s_env->env[i - 1] = parts[1].part;
	return (0);
}

void	copy_env(char **envp, t_env *s_env)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	s_env->env = ft_calloc((i + 1) * sizeof(char *), 1);
	s_env->size = i;
	i = 0;
	while (envp[i])
	{
		s_env->env[i] = ft_strdup(envp[i]);
		i++;
	}
}

static int	export_attribute(t_env *s_env, char *attr)
{
	int		i;
	char	**copy;

	i = 0;
	while (s_env->env[i])
		i++;
	if (i == s_env->size)
	{
		copy = ft_calloc((s_env->size + 11) * sizeof(char *), 1);
		i = 0;
		while (s_env->env[i])
		{
			copy[i] = ft_calloc(ft_strlen(s_env->env[i]) + 1, 1);
			ft_memcpy(copy[i], s_env->env[i], ft_strlen(s_env->env[i]));
			i++;
		}
		ft_free(s_env);
		s_env->env = copy;
		s_env->size += 10;
	}
	s_env->env[i] = ft_calloc(ft_strlen(attr) + 1, 1);
	ft_memmove(s_env->env[i], attr, ft_strlen(attr));
	return (0);
}

static void	ft_free(t_env *s_env)
{
	int	i;

	i = 0;
	while (s_env->env[i])
	{
		free(s_env->env[i]);
		i++;
	}
	free(s_env->env);
}
