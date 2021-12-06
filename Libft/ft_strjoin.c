#include "libft.h"
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		l1;
	int		l2;

	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen((char *)s1);
	l2 = ft_strlen((char *)s2);
	str = malloc(l1 + l2 + 1);
	if (!str)
		return (0);
	ft_memmove(str, (char *)s1, l1);
	ft_memmove(str + l1, (char *)s2, l2);
	str[l1 + l2] = '\0';
	return (str);
}
