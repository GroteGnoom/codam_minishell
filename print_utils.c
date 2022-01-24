/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/24 10:32:13 by daniel        #+#    #+#                 */
/*   Updated: 2022/01/24 14:37:45 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "./Libft/libft.h"

void	print_parts(t_part *parts)
{
	int		i;

	i = 0;
	while (parts[i].part)
	{
		printf("-%s- type: %d\n", parts[i].part, parts[i].type);
		i++;
	}
	printf("\n");
}

void	print_strs(char **strs)
{
	int		i;

	i = 0;
	while (strs[i])
	{
		perror(strs[i]);
		i++;
	}
}

void	ft_print_line_nr(int line_nr)
{
	ft_putstr_fd(": line ", 2);
	ft_putnbr_fd(line_nr, 2);
	ft_putstr_fd(": ", 2);
}

void	ft_print_shell_line(t_env *s_env)
{
	ft_putstr_fd(SHELL_NAME, 2);
	if (isatty(s_env->term_in))
		ft_putstr_fd(": ", 2);
	else
		ft_print_line_nr(s_env->line_nr);
}
