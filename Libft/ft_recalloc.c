/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:23:28 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/16 14:49:42 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_recalloc(void *p, size_t size, size_t old_size)
{
	void	*new;

	new = ft_calloc(size, 1);
	ft_memcpy(new, p, old_size);
	free(p);
	return (new);
}
