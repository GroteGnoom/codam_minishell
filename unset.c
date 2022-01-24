/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:13:14 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 13:51:35 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	ft_unset(t_part *parts, t_env *s_env)
{
	int		i;

	i = 0;
	if (!parts[1].part)
		return (0);
	if (check_identifier(parts[1].part, 1))
		return (ft_invalid_identifier(parts, 0, s_env));
	while (i < s_env->size && \
	!ft_strnstr(s_env->env[i], parts[1].part, ft_strlen(parts[1].part)))
		i++;
	if (i >= s_env->size)
		return (1);
	free(s_env->env[i]);
	s_env->env[i] = s_env->env[s_env->size -1];
	s_env->env[s_env->size - 1] = NULL;
	s_env->size--;
	return (0);
}
