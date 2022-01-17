/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/17 14:28:13 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "get_next_line/get_next_line.h"

int	global = 0;

static int	ft_redir_args(char **args, int line_nr);

static void	sigint_here_doc_handler(int sig)
{
	int pipefd[2];
	global = 1;
	(void) sig;
	if (pipe(pipefd) < 0)
		perror("Pipe: ");
	dup2(pipefd[0], STDIN_FILENO);
	write(pipefd[1], "\n\n", 2);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	here_doc(char *final, int line_nr, t_part *parts, t_pipe pipex)
{
	char	**args;
	char	*line;
	int		term;
	int		size;
	int		ret;
	int		atty;

	signal(SIGINT, sigint_here_doc_handler);
	if (!final)
		return (ft_syntax_error(parts, 0, line_nr, "newline"));
	term = 0;
	atty = isatty(STDIN_FILENO);
	if (atty)
	{
		term = dup(STDOUT_FILENO);
		if (dup2(pipex.term_in, STDOUT_FILENO) < 0)
			return (ft_redir_error("dup2", "", line_nr));
	}
	if (dup2(pipex.term_in, STDIN_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	if (isatty(STDIN_FILENO))
		line = readline("here_doc> ");
	else
		line = get_next_line(STDIN_FILENO);
	size = 2;
	args = ft_calloc(1 * sizeof(char *), 1);
	while (line)
	{
		if (global == 1)
		{
			free(line);
			if (atty && dup2(term, STDOUT_FILENO) < 0)
				return (ft_redir_error("dup2", "", line_nr));
			return (1);
		}
		if (!isatty(STDIN_FILENO))
			line = ft_strtrim_free(&line, "\n");
		if (!ft_strcmp(line, final))
			break ;
		args = ft_realloc(args, (size * sizeof(char *)), \
				((size - 1) * sizeof(char *)));
		args[size - 1] = NULL;
		args[size - 2] = ft_strjoin(line, "\n");
		free(line);
		if (isatty(STDIN_FILENO))
			line = readline("here_doc> ");

		else
			line = get_next_line(STDIN_FILENO);
		size++;
	}
	free(line);
	ret = ft_redir_args(args, line_nr);
	if (atty && dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	return (ret);
}

static int	ft_redir_args(char **args, int line_nr)
{
	int		pipefd[2];
	int		i;

	if (pipe(pipefd) < 0)
		perror("Pipe: ");
	i = 0;
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	while (args[i])
	{
		ft_putstr_fd(args[i], pipefd[1]);
		i++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	ft_free_strs(args);
	return (0);
}
