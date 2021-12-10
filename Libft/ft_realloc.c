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
