/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:23:28 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:23:29 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *p, size_t size, size_t old_size)
{
	void	*new;

	new = malloc(size);
	ft_memcpy(new, p, old_size);
	free(p);
	return (new);
}
