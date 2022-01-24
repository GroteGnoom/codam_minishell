/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/23 13:52:00 by daniel        #+#    #+#                 */
/*   Updated: 2022/01/24 14:36:46 by dnoom         ########   odam.nl         */
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

int	ft_syntax_error_eof(t_env *s_env)
{
	ft_putstr_fd(SHELL_NAME, 2);
	if (!isatty(s_env->term_in))
		ft_print_line_nr(s_env->line_nr + 1);
	else
		ft_putstr_fd(": ", 2);
	ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	return (2);
}

int	ft_redir_error(char *str, char *str2, t_env *s_env)
{
	if (!str2)
		perror(str);
	else
	{
		ft_print_shell_line(s_env);
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

int	ft_exit_error(int too_many, char *arg, t_env *s_env)
{
	ft_print_shell_line(s_env);
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

int	ft_home_not_set(t_part *parts, int i, t_env *s_env, char *envvar)
{
	ft_print_shell_line(s_env);
	ft_putstr_fd(parts[i].part, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(envvar, 2);
	ft_putstr_fd(" not set\n", 2);
	return (1);
}
