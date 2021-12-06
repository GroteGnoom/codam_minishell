#include "libft.h"
void	*ft_memset(void *str, int val, size_t len)
{
	int		i;
	char	*str1;

	i = 0;
	str1 = (void *)str;
	while (len > 0)
	{
		len--;
		str1[i] = val;
		i++;
	}
	return ((void *)str1);
}
