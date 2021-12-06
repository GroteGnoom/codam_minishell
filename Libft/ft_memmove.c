#include "libft.h"
void	*ft_memmove(void *dst, void *src, size_t len)
{
	char	*dst1;
	char	*src1;
	size_t	i;

	i = 0;
	dst1 = (void *)dst;
	src1 = (void *)src;
	if (!dst1 && !src1)
		return (0);
	if (dst1 > src1)
	{
		while (len > 0)
		{
			len--;
			dst1[len] = src1[len];
		}
	}
	while (i < len)
	{
		dst1[i] = src1[i];
		i++;
	}
	return ((void *)dst1);
}
