/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/12 10:13:31 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	here_doc(char *final);

int	redirect_here_doc(t_part *parts, int line_nr)
{
	char	*final;
	int		i;

	i = 0;
	line_nr = i;
	while (parts[i].part && ft_strcmp(parts[i].part, "<<"))
		i++;
	final = ft_strdup(parts[i + 1].part);
	here_doc(final);
	free(final);
	return (line_nr);
}

static void	here_doc(char *final)
{
	char	**args;
	char	*line;
	int		size;

	line = readline("here_doc> ");
	size = 2;
	args = ft_calloc(1 * sizeof(char *), 1);
	while (line)
	{
		if (!ft_strcmp(line, final))
			break ;
		args = ft_realloc(args, (size * sizeof(char *)), \
		((size - 1) * sizeof(char *)));
		args[size - 1] = NULL;
		args[size - 2] = ft_strjoin(line, "\n");
		free(line);
		line = readline("here_doc> ");
		size++;
	}
	free(line);
	ft_redir_args(args);
}

void	ft_redir_args(char **args)
{
	int		pipefd[2];
	int		i;

	pipe(pipefd);
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], pipefd[1]);
		i++;
	}
	if (dup2(pipefd[0], STDIN_FILENO))
		return ;
	close(pipefd[0]);
	close(pipefd[1]);
	ft_free_strs(args);
}
