/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:22:13 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:22:15 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (len + 1 < dstsize)
		ft_memmove(dst, (void *)src, len + 1);
	else if (dstsize > 0)
	{
		ft_memmove(dst, (void *)src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (len);
}
