/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:13:14 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/28 14:11:38 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	ft_unset(t_part *parts, t_env *s_env, int line_nr)
{
	char	*env;
	int		i;

	i = 0;
	if (!parts[1].part)
		return (0);
	if (check_identifier(parts[1].part, 1))
		return (ft_invalid_identifier(parts, 0, line_nr));
	while (i < s_env->size && \
	!ft_strnstr(s_env->env[i], parts[1].part, ft_strlen(parts[1].part)))
		i++;
	if (i >= s_env->size)
		return (1);
	env = ft_strchr(s_env->env[i], '=');
	if (env != 0)
		ft_substr_free(&s_env->env[i], 0, \
		ft_strlen(s_env->env[i]) - ft_strlen(env));
	return (0);
}
