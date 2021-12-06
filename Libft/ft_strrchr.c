#include "libft.h"
char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*found;
	const char	*str1;

	i = ft_strlen((char *)s);
	found = 0;
	if (c == '\0')
		return (ft_strchr(s, '\0'));
	str1 = ft_strchr(s, c);
	while (str1 != 0)
	{
		found = str1;
		s = str1 + 1;
		str1 = ft_strchr(s, c);
	}
	return ((char *)found);
}
