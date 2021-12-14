/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_wildcard.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 15:17:24 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/14 15:39:53 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

static void	expand_wild(char **part);

void	expand_wildcard(t_part *parts)
{
	while (parts->part)
	{
		if (parts->type == NORMAL)
			return ;
			// expand_wild(&(parts->part));
		parts++;
	}
}

static void	expand_wild(char **part)
{
	char	*str;
	int		i;

	i = 0;
	str = *part;
	while (str[i])
	{
		if (str[i] == '*')
		{
			*part = ft_wildcard(*part);
			return ;
		}
		i++;
	}
}
