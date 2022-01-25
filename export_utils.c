/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 10:47:39 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/25 10:48:11 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <termios.h>
#include <stdio.h>

int	check_identifier(char *str, int unset)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=' || str[0] == '+')
		return (1);
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			i++;
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

void	expand_env(t_env *s_env)
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
}
