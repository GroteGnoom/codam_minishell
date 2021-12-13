/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:22:28 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:22:31 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_free(char **s1, char const *s2)
{
	char	*str;
	int		l1;
	int		l2;

	if (!s1 || !s2)
		return ;
	l1 = ft_strlen(*s1);
	l2 = ft_strlen((char *)s2);
	str = malloc(l1 + l2 + 1);
	if (!str)
		return ;
	ft_memmove(str, *s1, l1);
	ft_memmove(str + l1, (char *)s2, l2);
	str[l1 + l2] = '\0';
	free(*s1);
	*s1 = str;
}
