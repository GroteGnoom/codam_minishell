/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 11:30:25 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/15 11:36:38 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contains(char *s1, char *set, int n);

char	*ft_strtrim_free(char **s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!s1 || !set)
		return (0);
	i = 0;
	j = 0;
	while ((ft_contains(*s1 + i, (char *)set, 1)))
		i++;
	j = ft_strlen(*s1);
	if (!j || i == j)
		return (ft_strdup("\0"));
	while ((ft_contains(*s1 + j - 1, (char *)set, 1)))
		j--;
	len = j - i;
	str = malloc(len + 1);
	if (!str)
		return (0);
	ft_memcpy(str, *s1 + i, len);
	str[len] = '\0';
	free(*s1);
	return (str);
}

static int	ft_contains(char *s1, char *set, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n)
	{
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
