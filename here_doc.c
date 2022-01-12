/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/12 14:12:41 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "get_next_line/get_next_line.h"

static int	ft_redir_args(char **args, int line_nr);

int	here_doc(char *final, int line_nr, t_part *parts, t_pipe pipex)
{
	char	**args;
	char	*line;
	int		size;
	int		ret;

	if (!final)
		return (ft_syntax_error(parts, 0, line_nr, "newline"));
	if (dup2(pipex.term_out, STDOUT_FILENO) < 0 || \
			dup2(pipex.term_in, STDIN_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	if (isatty(STDIN_FILENO))
		line = readline("here_doc> ");
	else
		line = get_next_line(STDIN_FILENO);
	size = 2;
	args = ft_calloc(1 * sizeof(char *), 1);
	while (line)
	{
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
	return (ret);
}

static int	ft_redir_args(char **args, int line_nr)
{
	int		pipefd[2];
	int		pipe_fd;
	int		i;

	if (pipe(pipefd) < 0)
		perror("Pipe: ");
	pipe_fd = dup(STDOUT_FILENO);
	if (pipe_fd < 0)
		return (ft_redir_error("dup", "", line_nr));
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], pipefd[1]);
		i++;
	}
	if (dup2(pipefd[0], STDIN_FILENO) || dup2(pipe_fd, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", "", line_nr));
	close(pipefd[0]);
	close(pipefd[1]);
	ft_free_strs(args);
	return (0);
}
