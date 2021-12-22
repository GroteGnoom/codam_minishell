/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:21:55 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:21:57 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		i;
	size_t	len;

	len = ft_strlen(s1) + 1;
	if ((size_t)ft_strlen(s2) < len)
		len = ft_strlen(s2) + 1;
	if (!len)
		len++;
	if (len < n)
		n = len;
	i = ft_memcmp(s1, s2, n);
	if (i < 0)
		return (-1);
	else if (i > 0)
		return (1);
	return (0);
}
