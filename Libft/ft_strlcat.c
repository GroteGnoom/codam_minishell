/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:22:20 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:22:22 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l;

	l = ft_strlen(dst);
	if (dstsize > l)
		ft_strlcpy(dst + l, (char *)src, dstsize - l);
	else
		return (ft_strlen(src) + dstsize);
	l += ft_strlen(src);
	return (l);
}
