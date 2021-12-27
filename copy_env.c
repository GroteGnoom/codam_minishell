/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/27 13:35:53 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/27 13:35:54 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

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
