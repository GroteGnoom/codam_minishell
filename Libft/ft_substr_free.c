/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:20:56 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:20:58 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_substr_free(char **s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	l;
	unsigned int	i;

	if (!s)
		return ;
	l = ft_strlen(*s);
	i = 0;
	if (l <= start)
	{
		str = ft_strdup("\0");
		*s = str;
		return ;
	}
	if (len > l)
		len = l;
	str = malloc(len + 1);
	if (!str)
		return ;
	ft_memmove(str, *s + start, len);
	str[len] = '\0';
	free(*s);
	*s = str;
}
