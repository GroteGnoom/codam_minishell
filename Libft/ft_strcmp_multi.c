/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp_multi.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:22:53 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/06 14:15:28 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_multi(const char *s1, char **s2)
{
	while (*s2)
	{
		if (!ft_strcmp(s1, *s2))
			return (0);
		s2++;
	}
	return (1);
}
