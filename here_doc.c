/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:11:35 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>

char	**here_doc(char *final)
{
	char	**args;
	char	*line;
	int		size;

	size = 2;
	line = readline("here_doc> ");
	args = malloc(1 * sizeof(char *));
	while (line)
	{
		if (!ft_strcmp(line, final))
		{
			return (args);
		}
		args = ft_realloc(args, (size * sizeof(char *)), \
		((size - 1) * sizeof(char *)));
		args[size - 1] = NULL;
		args[size - 2] = ft_strdup(line);
		free(line);
		line = readline("here_doc> ");
		size++;
	}
	return (0);
}
