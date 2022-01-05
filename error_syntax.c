/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_syntax.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/05 10:25:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/05 11:48:13 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"
#include <stdio.h>

int	ft_syntax_error(t_part *parts, int i, int line_nr, char *token)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_print_line_nr(line_nr);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);
		ft_putstr_fd(SHELL_NAME, 2);
		ft_print_line_nr(line_nr);
		ft_putstr_fd("`", 2);
		i = print_parts_error(parts);
		ft_putstr_fd(parts[i].part, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (2);
}
