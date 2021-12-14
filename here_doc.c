/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/14 10:38:00 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>

void	ft_redir_args(char **args);

char	**here_doc(char *final)
{
	char	**args;
	char	*line;
	int		size;

	line = readline("here_doc> ");
	size = 2;
	args = malloc(1 * sizeof(char *));
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
	ft_redir_args(args);
	return (0);
}

void	ft_redir_args(char **args)
{
	int		pipefd[2];
	int		term;
	int		i;

	i = 0;
	term = 0;
	pipe(pipefd);
	if (dup2(STDOUT_FILENO, term) < 0)
		return ;
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return ;
	close(pipefd[0]);
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDIN_FILENO);
		i++;
	}
	close(STDIN_FILENO);
	if (dup2(term, STDOUT_FILENO) < 0)
		return ;
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return ;
	close(pipefd[0]);
	close(pipefd[1]);
}
