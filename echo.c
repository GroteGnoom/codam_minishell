/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:56 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/19 14:13:16 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

static int	ft_write_echo(t_part *parts, int i, int nr_parts);

static int	ft_check_flags(char *flag);

int	ft_echo(int nr_parts, t_part *parts)
{
	int	ret;
	int	i;

	i = 1;
	while (parts[i].part && !ft_check_flags(parts[i].part))
		i++;
	ret = ft_write_echo(parts, i, nr_parts);
	if (!ret && ft_check_flags(parts[1].part))
	{
		if (write(1, "\n", 1) < 0)
			return (1);
	}
	return (ret);
}

static int	ft_check_flags(char *flag)
{
	int	i;

	i = 0;
	if (!flag || !flag[i])
		return (1);
	if (flag[i] == '-')
		i++;
	while (flag[i] && flag[i] == 'n')
		i++;
	if (!flag[i])
		return (0);
	return (1);
}

static int	ft_write_echo(t_part *parts, int i, int nr_parts)
{
	while (i < nr_parts)
	{
		if (write(1, parts[i].part, ft_strlen(parts[i].part)) < 0)
			return (1);
		if (i < nr_parts - 1)
		{
			if (write(1, " ", 1) < 0)
				return (1);
		}
		i++;
	}
	return (0);
}
