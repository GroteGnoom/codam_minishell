/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:22:47 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/16 13:58:22 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *s1, size_t size)
{
	char	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (0);
	ft_memmove(ptr, (void *)s1, size);
	return (ptr);
}
