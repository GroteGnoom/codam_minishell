/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_built_in.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 12:54:54 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/07 14:12:21 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	is_built_in(char *str, int nr_parts, t_part *parts, t_env *s_env)
{
	if (!ft_strcmp(str, "exit"))
		return(ft_exit(nr_parts, parts, s_env->line_nr));
	else if (!ft_strcmp(str, "echo"))
		return(ft_echo(nr_parts, parts));
	else if (!ft_strcmp(str, "cd"))
		return(ft_cd(parts, s_env->line_nr));
	else if (!ft_strcmp(str, "pwd"))
		return(ft_pwd());
	else if (!ft_strcmp(str, "env"))
		return(ft_env(s_env->env));
	else if (!ft_strcmp(str, "export"))
		return(ft_export(parts, s_env));
	else if (!ft_strcmp(str, "unset"))
		return(ft_unset(parts, s_env));
	else
		return (ft_executable(nr_parts, parts, s_env));
}
