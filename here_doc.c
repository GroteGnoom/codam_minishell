/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/18 09:47:20 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "get_next_line/get_next_line.h"

int	g_global = 0;

static int	ft_redir_args(char **args, int line_nr);

int	here_doc(char *final, int line_nr, t_part *parts, t_pipe pipex)
{
	char	**args;
	char	*line;
	int		term;
	int		size;
	int		ret;
	int		atty;

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
	line = next_line();
	size = 2;
	args = ft_calloc(1 * sizeof(char *), 1);
	while (line)
	{
		if (g_global == 1)
			return (return_from_sigint(line, args, term, line_nr));
		if (!isatty(STDIN_FILENO))
			line = ft_strtrim_free(&line, "\n");
		if (!ft_strcmp(line, final))
			break ;
		add_to_args_free(&args, line, &size);
		line = next_line();
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
