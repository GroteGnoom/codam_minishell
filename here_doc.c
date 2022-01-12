/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/12 10:35:58 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	ft_redir_args(char **args, int line_nr);

int	here_doc(char *final, int line_nr, t_part *parts)
{
	char	**args;
	char	*line;
	int		size;
	int		ret;

	if (!final)
		return (ft_syntax_error(parts, 0, line_nr, "newline"));
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
	ret = ft_redir_args(args, line_nr);
	return (ret);
}

static int	ft_redir_args(char **args, int line_nr)
{
	int		pipefd[2];
	int		i;

	if (pipe(pipefd) < 0)
		perror("Pipe: ");
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], pipefd[1]);
		i++;
	}
	if (dup2(pipefd[0], STDIN_FILENO))
		return (ft_redir_error("dup2", "", line_nr));
	close(pipefd[0]);
	close(pipefd[1]);
	ft_free_strs(args);
	return (0);
}
