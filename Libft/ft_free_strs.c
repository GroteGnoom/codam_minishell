/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_strs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 09:36:56 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/14 09:36:59 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_strs(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
