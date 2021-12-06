#include "libft.h"
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				l;

	str = (const unsigned char *)s;
	l = 0;
	while (l < n)
	{
		if (str[l] == (unsigned char)c)
			return ((void *)&str[l]);
		l++;
	}
	return (0);
}
