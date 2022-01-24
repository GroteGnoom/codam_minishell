/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/27 13:35:53 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 13:58:33 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>

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
	s_env->term_out = dup(STDOUT_FILENO);
	s_env->term_in = dup(STDIN_FILENO);
	if (s_env->term_out < 0 || s_env->term_in < 0)
		perror("dup");
}

void	ft_free_env(t_env *s_env)
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
