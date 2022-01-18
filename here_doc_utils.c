/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 08:54:00 by dnoom         #+#    #+#                 */
/*   Updated: 2022/01/18 10:24:56 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include "get_next_line/get_next_line.h"
#include <unistd.h>
#include <signal.h>
#include "Libft/libft.h"

extern int	g_global;

static void	sigint_here_doc_handler(int sig)
{
	int	pipefd[2];

	g_global = 1;
	(void) sig;
	if (pipe(pipefd) < 0)
		perror("Pipe: ");
	dup2(pipefd[0], STDIN_FILENO);
	write(pipefd[1], "\n\n", 2);
	close(pipefd[0]);
	close(pipefd[1]);
}

char	*next_line(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		g_global = 0;
		signal(SIGINT, sigint_here_doc_handler);
		line = readline("here_doc> ");
		signal(SIGINT, sigint_handler);
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
	}
	return (line);
}

int	return_from_sigint(char *line, char **args, int term, int line_nr)
{
	free(line);
	ft_free_strs(args);
	if (isatty(STDIN_FILENO) && dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	return (1);
}

void	add_to_args_free(char ***args, char *line)
{
	int	size;

	size = ft_count_strs(*args) + 2;
	*args = ft_realloc(*args, (size * sizeof(char *)), \
			((size - 1) * sizeof(char *)));
	(*args)[size - 1] = NULL;
	(*args)[size - 2] = ft_strjoin(line, "\n");
	free(line);
}
