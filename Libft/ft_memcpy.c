#include "libft.h"
void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*dst1;
	const char	*src1;

	dst1 = (char *)dst;
	src1 = (const char *)src;
	if (!dst1 && !src1)
		return (0);
	while (len)
	{
		*dst1 = *src1;
		dst1++;
		src1++;
		len--;
	}
	return (dst);
}
