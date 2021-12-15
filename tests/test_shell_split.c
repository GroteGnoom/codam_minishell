/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_shell_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 14:34:40 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/15 14:35:40 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
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

void	print_parts(char *str)
{
	t_part	*parts;

	parts = ft_shell_split(str, 13);
	print_parts2(parts);
	ft_free_parts(parts);
}

int	main(void)
{
	print_parts("a");
	print_parts("a|a");
	print_parts("a | a");
	print_parts("a \"|\" a");
	print_parts("a>a");
	print_parts("a > a");
	print_parts("a \">\" a");
	print_parts("a>>a");
	print_parts("a >> a");
	print_parts("a \">>\" a");
	print_parts("'' '' ''");
	print_parts("''hallo hallo'' ''");
	print_parts("$? asd'$?'fasdf dsfasdf\"bla$?\" ''");
}
