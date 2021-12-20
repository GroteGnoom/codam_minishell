/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:21:04 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:21:07 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	l;

	if (!s)
		return (0);
	l = ft_strlen(s);
	if (l <= start)
		return (ft_strdup("\0"));
	if (len > l)
		len = l;
	str = malloc(len + 1);
	if (!str)
		return (0);
	ft_memmove(str, (char *)&s[start], len);
	str[len] = '\0';
	return (str);
}
