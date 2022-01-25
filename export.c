/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:23 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/25 11:37:10 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <termios.h>
#include <stdio.h>

static int	export_new_var(t_env *s_env, char *envname, char *part);

int	ft_export(t_part *parts, t_env *s_env)
{
	char	*envname;
	char	*plus_pos;
	int		err;

	if (!parts[1].part || parts[1].type != NORMAL)
		return (ft_export_print(s_env->env));
	if (check_identifier(parts[1].part, 0))
		return (ft_invalid_identifier(parts, 0, s_env));
	envname = ft_strchr(parts[1].part, '=');
	plus_pos = ft_strchr(parts[1].part, '+');
	if (plus_pos && plus_pos[1] == '=')
		envname--;
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
	char	*plus_pos;
	int		i;

	i = 0;
	prev_var = get_prev_var(s_env, envname, &i);
	if (i == s_env->size && !prev_var)
		expand_env(s_env);
	if (!prev_var)
		return (export_new_var(s_env, envname, part));
	if (prev_var)
		i -= 1;
	plus_pos = ft_strchr(part, '+');
	if (plus_pos && plus_pos[1] == '=')
		ft_strjoin_free(&s_env->env[i], part + ft_strlen(envname) + 2);
	else if (ft_strchr(part, '='))
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

static int	export_new_var(t_env *s_env, char *envname, char *part)
{
	char	*new_var;
	int		i;

	i = 0;
	while (s_env->env[i])
		i++;
	if (!ft_strchr(part, '+'))
		s_env->env[i] = ft_strdup(part);
	else
	{
		new_var = ft_strjoin(envname, part + ft_strlen(envname) + 1);
		s_env->env[i] = new_var;
	}
	return (0);
}
