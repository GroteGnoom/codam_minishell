/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:23 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 11:51:29 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <termios.h>
#include <stdio.h>

static int	export_attribute(t_env *s_env, char *attr);

int	ft_export(t_part *parts, t_env *s_env)
{
	char	*envname;
	int		err;

	if (!parts[1].part || parts[1].type != NORMAL)
		return (ft_export_print(s_env->env));
	if (check_identifier(parts[1].part, 0))
		return (ft_invalid_identifier(parts, 0, s_env->line_nr));
	envname = ft_strchr(parts[1].part, '=');
	if (envname)
		envname = ft_substr(parts[1].part, 0, ft_strlen(parts[1].part) \
		- ft_strlen(envname));
	else
		envname = ft_strdup(parts[1].part);
	err = ft_export_var(s_env, parts[1].part, envname);
	free(envname);
	return (err);
}

int	ft_export_var(t_env *s_env, char *part, char *envname)
{
	char	*prev_var;
	int		i;

	i = 0;
	prev_var = get_prev_var(s_env, envname, &i);
	if (i == s_env->size && !prev_var)
		return (export_attribute(s_env, part));
	if (prev_var)
		i -= 1;
	if (ft_strchr(part, '='))
	{
		free(s_env->env[i]);
		s_env->env[i] = ft_strdup(part);
	}
	return (0);
}

char	*get_prev_var(t_env *s_env, char *envname, int *i)
{
	char	*prev_var;
	int		len;

	len = ft_strlen(envname);
	prev_var = NULL;
	while (s_env->env[*i] && *i < s_env->size && !prev_var)
	{
		prev_var = ft_strnstr(s_env->env[*i], envname, len);
		if (prev_var && s_env->env[*i][len] != 0 && s_env->env[*i][len] != '=')
			prev_var = NULL;
		*i += 1;
	}
	return (prev_var);
}

int	check_identifier(char *str, int unset)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (1);
	if (str[0] == '=')
		return (1);
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (unset)
				return (1);
			else
				return (0);
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
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
		ft_free_env(s_env);
		s_env->env = copy;
		s_env->size += 10;
	}
	s_env->env[i] = ft_calloc(ft_strlen(attr) + 1, 1);
	ft_memmove(s_env->env[i], attr, ft_strlen(attr));
	return (0);
}
