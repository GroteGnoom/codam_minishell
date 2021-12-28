/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_built_in.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 12:54:54 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/28 14:17:22 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	is_built_in(char *str, int nr_parts, t_part *parts, t_env *s_env, int line_nr)
{
	int	last_exit_status;

	if (!ft_strcmp(str, "exit"))
		last_exit_status = ft_exit(nr_parts, parts, line_nr);
	else if (!ft_strcmp(str, "echo"))
		last_exit_status = ft_echo(nr_parts, parts);
	else if (!ft_strcmp(str, "cd"))
		last_exit_status = ft_cd(parts, line_nr);
	else if (!ft_strcmp(str, "pwd"))
		last_exit_status = ft_pwd();
	else if (!ft_strcmp(str, "env"))
		last_exit_status = ft_env(s_env->env);
	else if (!ft_strcmp(str, "export"))
		last_exit_status = ft_export(parts, s_env, line_nr);
	else if (!ft_strcmp(str, "unset"))
		last_exit_status = ft_unset(parts, s_env, line_nr);
	else
		return (300);
	return (last_exit_status);
}
