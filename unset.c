/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:13:14 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:13:17 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	ft_unset(char **args, t_env *s_env)
{
	char	*env;
	int		i;

	i = 0;
	while (i < s_env->size && \
	!ft_strnstr(s_env->env[i], args[1], ft_strlen(args[1])))
		i++;
	if (i >= s_env->size)
		return (1);
	env = ft_strchr(s_env->env[i], '=');
	if (env != 0)
		ft_substr_free(&s_env->env[i], 0, \
		ft_strlen(s_env->env[i]) - ft_strlen(env));
	return (0);
}
