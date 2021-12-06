char	*ft_strchr(const char *s, int c)
{
	char	*s1;

	s1 = (char *)s;
	if (c == '\0')
	{
		while (*s1)
			s1++;
		return (s1);
	}
	while (*s1)
	{
		if (*s1 == (unsigned char)c)
			return (s1);
		s1++;
	}
	return (0);
}
