/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:21:29 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:21:31 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*found;
	const char	*str1;

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
