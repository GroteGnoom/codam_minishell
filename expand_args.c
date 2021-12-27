/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:31 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/24 09:57:36 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "stdio.h"
#include "minishell.h"

void	ft_replace(char **sp, int start, int len, char *rep)
{
	char	*new;
	int		new_length;
	char	*last_part;

	new_length = ft_strlen(*sp) + ft_strlen(rep) - len + 1;
	last_part = *sp + start + len;
	new = ft_calloc(new_length, 1);
	ft_memcpy(new, *sp, start);
	ft_memcpy(new + start, rep, ft_strlen(rep));
	ft_memcpy(new + start + ft_strlen(rep), last_part, \
		ft_strlen(last_part));
	free(*sp);
	*sp = new;
}

char	*ft_search_name(t_env *s_env, char *envname, int envlen)
{
	char	*values;
	int		i;

	i = 0;
	while (s_env->env[i])
	{
		if (!ft_strncmp(s_env->env[i], envname, envlen) && \
		s_env->env[i][envlen] == '=')
		{
			values = s_env->env[i] + envlen + 1;
			free(envname);
			return (values);
		}
		i++;
	}
	return (NULL);
}

int	ft_insert_exit_status(char **sp, int i, int last_exit_status)
{
	char	*env;

	if ((*sp)[i] == '?')
	{
		env = ft_itoa(last_exit_status);
		ft_replace(sp, i - 1, 2, env);
		free(env);
		return (1);
	}
	return (0);
}

void	expand_args(char **sp, int last_exit_status, t_env *s_env)
{
	int		i;
	char	*envname;
	char	*env;
	int		envlen;

	i = 0;
	while ((*sp)[i])
	{
		if ((*sp)[i] == '$')
		{
			i++;
			if (ft_insert_exit_status(sp, i, last_exit_status))
				continue ;
			envlen = 0;
			while ((*sp)[i + envlen] && (*sp)[i + envlen] != ' '
				&& (*sp)[i + envlen] != '*')
				envlen++;
			envname = ft_substr(*sp, i, envlen);
			env = ft_search_name(s_env, envname, envlen);
			if (!env)
				env = "";
			ft_replace(sp, i - 1, envlen + 1, env);
		}
		i++;
	}
}

void	expand_unquoted_args(t_part *parts, int last_exit_status, t_env *s_env)
{
	while (parts->part)
	{
		if (parts->type == NORMAL || parts->type == DOUBLE_QUOTED)
			expand_args(&(parts->part), last_exit_status, s_env);
		parts++;
	}
}
