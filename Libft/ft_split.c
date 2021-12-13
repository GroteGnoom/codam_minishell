/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:23:06 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:23:08 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char *s, char c);

static char	*ft_copy(char *arr, char *s, char c);

static char	*ft_next_word(char *s, char c);

static void	ft_free(char **arr, int i);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;
	int		i;

	if (!s)
		return (0);
	i = 0;
	words = ft_words((char *)s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (0);
	while (i < words)
	{
		arr[i] = ft_copy(arr[i], (char *)s, c);
		if (!arr[i])
		{
			ft_free(arr, i);
			return (0);
		}
		s = ft_next_word((char *)s, c);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static void	ft_free(char **arr, int i)
{
	while (i > 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

static int	ft_words(char *s, char c)
{
	int	w;

	w = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			w++;
		while (*s != c && *s)
			s++;
	}
	return (w);
}

static char	*ft_copy(char *arr, char *s, char c)
{
	int	len;

	while (*s == c)
		s++;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	arr = malloc((len + 1) * sizeof(char));
	if (!arr)
		return (0);
	ft_strlcpy(arr, s, len + 1);
	return (arr);
}

static char	*ft_next_word(char *s, char c)
{
	while (*s == c)
		s++;
	while (*s != c && *s)
		s++;
	return (s);
}
