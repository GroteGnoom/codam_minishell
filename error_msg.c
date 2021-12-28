/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/23 13:52:00 by daniel        #+#    #+#                 */
/*   Updated: 2021/12/28 14:06:12 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"
#include <stdio.h>

int	ft_syntax_error(t_part *parts, int i, int line_nr)
{
	(void) line_nr;
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
		i = -1;
		while (parts[++i + 1].part)
		{
			ft_putstr_fd(parts[i].part, 2);
			ft_putchar_fd(' ', 2);
		}
		ft_putstr_fd(parts[i].part, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (1);
}

int	ft_redir_error(char *str, char *str2, int line_nr)
{
	(void) line_nr;
	if (!str2)
		perror(str);
	else
	{
		ft_putstr_fd(SHELL_NAME, 2);
		if (isatty(STDIN_FILENO))
			ft_putstr_fd(": ", 2);
		else
			ft_putstr_fd(": line 1: ", 2);
		if (ft_strcmp(SHELL_NAME, str))
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(str2, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (1);
}

int	ft_invalid_identifier(t_part *parts, int i, int line_nr)
{
	(void) line_nr;
	ft_putstr_fd(SHELL_NAME, 2);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd(": ", 2);
	else
		ft_putstr_fd(": line 1: ", 2);
	ft_putstr_fd(parts[i].part, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(parts[i + 1].part, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	ft_exit_error(int too_many, char *arg, int line_nr)
{
	(void) line_nr;
	ft_putstr_fd(SHELL_NAME, 2);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd(": ", 2);
	else
		ft_putstr_fd(": line 1: ", 2);
	ft_putstr_fd("exit: ", 2);
	if (too_many)
		ft_putstr_fd("too many arguments\n", 2);
	else {
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	return (1);
}
