/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:24:43 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:24:45 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*cpy;
	int		len;

	if (!lst)
		return (0);
	cpy = lst;
	len = 1;
	while (cpy->next != 0)
	{
		cpy = cpy->next;
		len++;
	}
	return (len);
}
