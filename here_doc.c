/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/11 16:16:38 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	here_doc(char *final);

int	redirect_here_doc(t_part *parts, t_env *s_env)
{
	char	*final;
	pid_t	child;
	int		status;
	int		i;

	i = 0;
	s_env->line_nr = 1;
	final = ft_strdup(parts[i + 1].part);
	child = fork();
	if (child < 0)
		perror("Fork: ");
	if (child == 0)
		here_doc(final);
	waitpid(-1, &status, 0);
	free(final);
	return (0);
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
	ft_redir_args(args);
	exit(0);
}

void	ft_redir_args(char **args)
{
	int		pipefd[2];
	int		term_out;
	int		i;

	i = 0;
	term_out = dup(STDOUT_FILENO);
	if (term_out < 0)
		return ;
	pipe(pipefd);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return ;
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
	}
	if (dup2(term_out, STDOUT_FILENO) < 0)
		return ;
	close(pipefd[0]);
	close(pipefd[1]);
	ft_free_strs(args);
}
