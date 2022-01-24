/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 11:05:18 by daniel        #+#    #+#                 */
/*   Updated: 2022/01/24 11:49:46 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	get_env_name_length(char *env)
{
	int	len;

	len = 0;
	if (ft_isdigit(*env))
		len = 1;
	else
		while (env[len] && (ft_isalnum(env[len]) || env[len] == '_' ))
			len++;
	return (len);
}

void	ft_remove_part(t_part *parts)
{
	char	*old_part;

	old_part = parts->part;
	while (parts->part)
	{
		parts[0] = parts[1];
		parts++;
	}
	free(old_part);
}
