/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/23 13:52:00 by daniel        #+#    #+#                 */
/*   Updated: 2022/01/05 10:25:27 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"
#include <stdio.h>

int	print_parts_error(t_part *parts)
{
	int	i;

	i = 0;
	while (parts[i + 1].part)
	{
		ft_putstr_fd(parts[i].part, 2);
		ft_putchar_fd(' ', 2);
		i++;
	}
	return (i);
}

int	ft_syntax_error_eof(int line_nr)
{
	ft_putstr_fd(SHELL_NAME, 2);
	if (!isatty(STDIN_FILENO))
		ft_print_line_nr(line_nr + 1);
	ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	return (2);
}

int	ft_redir_error(char *str, char *str2, int line_nr)
{
	if (!str2)
		perror(str);
	else
	{
		ft_putstr_fd(SHELL_NAME, 2);
		if (isatty(STDIN_FILENO))
			ft_putstr_fd(": ", 2);
		else
			ft_print_line_nr(line_nr);
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
	ft_putstr_fd(SHELL_NAME, 2);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd(": ", 2);
	else
		ft_print_line_nr(line_nr);
	ft_putstr_fd(parts[i].part, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(parts[i + 1].part, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	ft_exit_error(int too_many, char *arg, int line_nr)
{
	ft_putstr_fd(SHELL_NAME, 2);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd(": ", 2);
	else
		ft_print_line_nr(line_nr);
	ft_putstr_fd("exit: ", 2);
	if (too_many)
		ft_putstr_fd("too many arguments\n", 2);
	else
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	return (1);
}
