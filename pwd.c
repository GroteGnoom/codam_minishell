/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:03 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:15:05 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <sys/syslimits.h>

int	ft_pwd(void)
{
	char	*buf;
	char	*print_str;

	buf = NULL;
	print_str = getcwd(buf, PATH_MAX);
	free(buf);
	if (write(1, print_str, ft_strlen(print_str)) < 0)
		return (1);
	if (write(1, "\n", 1) < 0)
		return (1);
	return (0);
}
