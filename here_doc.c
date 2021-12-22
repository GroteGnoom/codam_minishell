/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/17 14:54:30 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>

void		ft_redir_args(char **args, int nr_parts, \
t_part *parts, t_env *s_env);

static void	here_doc(char *final, int nr_parts, t_part *parts, t_env *s_env);

int	redirect_here_doc(int nr_parts, t_part *parts, t_env *s_env, int *exec)
{
	t_part	*new_args;
	char	*final;
	pid_t	child;
	int		status;
	int		i;

	i = 0;
	*exec = 1;
	new_args = ft_calloc((nr_parts) * sizeof(*parts), 1);
	while (ft_strcmp(parts[i].part, "<<") != 0)
	{
		new_args[i].part = ft_strdup(parts[i].part);
		i++;
	}
	final = ft_strdup(parts[i + 1].part);
	child = fork();
	if (child < 0)
		perror("Fork: ");
	if (child == 0)
		here_doc(final, i, new_args, s_env);
	waitpid(-1, &status, 0);
	ft_free_parts(new_args);
	free(final);
	return (0);
}

static void	here_doc(char *final, int nr_parts, t_part *parts, t_env *s_env)
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
	ft_redir_args(args, nr_parts, parts, s_env);
	exit(0);
}

void	ft_redir_args(char **args, int nr_parts, t_part *parts, t_env *s_env)
{
	int		pipefd[2];
	int		term_out;
	int		term_in;
	int		i;

	i = 0;
	term_out = 0;
	term_in = 1;
	pipe(pipefd);
	if (dup2(STDOUT_FILENO, term_out) < 0 || dup2(STDIN_FILENO, term_in) < 0)
		return ;
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return ;
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
	}
	if (dup2(term_out, STDOUT_FILENO) < 0 || dup2(pipefd[0], STDIN_FILENO) < 0)
		return ;
	close(pipefd[1]);
	ft_executable(nr_parts, parts, s_env);
	if (dup2(term_in, STDIN_FILENO) < 0)
		return ;
}
