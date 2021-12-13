/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:24:11 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:24:13 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int val, size_t len)
{
	int		i;
	char	*str1;

	i = 0;
	str1 = (void *)str;
	while (len > 0)
	{
		len--;
		str1[i] = val;
		i++;
	}
	return ((void *)str1);
}
