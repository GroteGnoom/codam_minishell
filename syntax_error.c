/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/23 13:52:00 by daniel        #+#    #+#                 */
/*   Updated: 2021/12/23 13:52:53 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"
#include <stdio.h>

int	ft_syntax_error(t_part *parts, int i)
{
	if (isatty(STDIN_FILENO))
		printf("%s: syntax error near unexpected token `%c'\n", \
		SHELL_NAME, parts[i].part[1]);
	else
	{
		printf("%s: line 1: syntax error near unexpected token \
			`%c'\n%s: line 1: `", \
		SHELL_NAME, parts[i].part[1], SHELL_NAME);
		i = 0;
		while (parts[i + 1].part)
		{
			printf("%s ", parts[i].part);
			i++;
		}
		printf("%s'\n", parts[i].part);
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
