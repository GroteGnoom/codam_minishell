/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:48 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:16:51 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <stdio.h>

//the env command should only show variables with a value,
//the export command shows everything, and alphabetically
//_=/usr/bin/env should be at the end? but we don't call /usr/bin/env
//we could, and the only export needs to be handled
int	ft_env(char **envp) //the order is not the same as bash
{
	while (*envp)
	{
		ft_putstr_fd(*envp, 1);
		ft_putchar_fd('\n', 1);
		envp++;
	}
	return (0);
}

void	print_env_export(char *env)
{
	int	len_before_equals;

	len_before_equals = 0;
	while (env[len_before_equals] && env[len_before_equals] != '=')
		len_before_equals++;
	len_before_equals++;
	ft_putstr_fd("declare -x ", 1);
	write(1, env, len_before_equals);
	ft_putchar_fd('"', 1);
	write(1, env + len_before_equals, ft_strlen(env) - len_before_equals);
	ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
}

int	ft_export_print(char **envp)
{
	char	*first;
	char	*last;
	int		i;

	if (!*envp)
		return (0);
	i = 0;
	first = NULL;
	while (1)
	{
		last = first;
		first = NULL;
		i = 0;
		while (envp[i])
		{
			if ((!first || (ft_strcmp(envp[i], first) < 0))
				&& (!last || ft_strcmp(envp[i], last) > 0))
				first = envp[i];
			i++;
		}
		if (!first)
			return (0);
		else
			print_env_export(first);
	}
}
