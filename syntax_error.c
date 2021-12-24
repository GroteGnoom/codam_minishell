/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/23 13:52:00 by daniel        #+#    #+#                 */
/*   Updated: 2021/12/24 13:29:05 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"
#include <stdio.h>

int	ft_syntax_error(t_part *parts, int i)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		ft_putchar_fd(parts[i].part[1], 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": line 1: syntax error near unexpected token `", 2);
		ft_putchar_fd(parts[i].part[1], 2);
		ft_putstr_fd("'\n", 2);
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": line 1: `", 2);
		i = 0;
		while (parts[i + 1].part)
		{
			ft_putstr_fd(parts[i].part, 2);
			ft_putchar_fd(' ', 2);
			i++;
		}
		ft_putstr_fd(parts[i].part, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (1);
}

int	ft_redir_error(char *str, char *str2)
{
	if (!str2)
		perror(str);
	else
	{
		write(1, str, ft_strlen(str));
		write(1, ": ", 2);
		write(1, str2, ft_strlen(str2));
		write(1, ": No such file or directory\n", 28);
	}
	return (1);
}
