/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 11:05:18 by daniel        #+#    #+#                 */
/*   Updated: 2021/12/28 11:05:28 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"

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
