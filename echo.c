/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:56 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:16:58 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	ft_echo(char **args, int nr_args)
{
	int	i;

	i = 1;
	if (!ft_strcmp(args[i], "-n"))
		i++;
	while (i < nr_args)
	{
		if (write(1, args[i], ft_strlen(args[i])) < 0)
			return (1);
		if (i < nr_args - 1)
		{
			if (write(1, " ", 1) < 0)
				return (1);
		}
		i++;
	}
	if (ft_strcmp(args[1], "-n"))
	{
		if (write(1, "\n", 1) < 0)
			return (1);
	}
	return (0);
}
