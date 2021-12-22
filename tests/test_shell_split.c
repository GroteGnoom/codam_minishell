/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_shell_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:34:40 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/16 16:32:00 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../Libft/libft.h"
#include "stdlib.h"

void	print_parts2(t_part *parts)
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

void	print_parts(char *str, t_env s_env)
{
	t_part	*parts;

	parts = ft_shell_split(str, 13, &s_env);
	print_parts2(parts);
	ft_free_parts(parts);
}

int	main(int argc, char **argv, char **env)
{
	t_env	s_env;

	(void) argc;
	(void) argv;
	copy_env(env, &s_env);
	print_parts("a", s_env);
	print_parts("a|a", s_env);
	print_parts("a | a", s_env);
	print_parts("a \"|\" a", s_env);
	print_parts("a>a", s_env);
	print_parts("a > a", s_env);
	print_parts("a \">\" a", s_env);
	print_parts("a>>a", s_env);
	print_parts("a >> a", s_env);
	print_parts("a \">>\" a", s_env);
	print_parts("'' '' ''", s_env);
	print_parts("''hallo hallo'' ''", s_env);
	print_parts("$? asd'$?'fasdf dsfasdf\"bla$?\" ''", s_env);
	print_parts("test_*.c", s_env);
}
