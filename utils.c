int	ft_count_strs(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
