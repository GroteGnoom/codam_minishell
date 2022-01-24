/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 09:52:34 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 13:53:02 by dnoom         ########   odam.nl         */
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

static int	ft_redir_args(char **args, t_env *s_env, int term);

static char	**ft_get_lines(char *final, int *ret, int term, t_env *s_env);

int	here_doc(char *final, t_env *s_env, t_part *parts)
{
	char	**args;
	int		term;
	int		ret;

	if (!final)
		return (ft_syntax_error(parts, 0, s_env, "newline"));
	term = 0;
	if (isatty(STDIN_FILENO))
		term = dup(STDOUT_FILENO);
	if (isatty(STDIN_FILENO))
		if (dup2(s_env->term_in, STDOUT_FILENO) < 0)
			return (ft_redir_error("dup2", "", s_env));
	args = ft_get_lines(final, &ret, term, s_env);
	if (ret)
		return (ret);
	return (ft_redir_args(args, s_env, term));
}

static char	**ft_get_lines(char *final, int *ret, int term, t_env *s_env)
{
	char	**args;
	char	*line;

	line = next_line(s_env);
	args = ft_calloc(1 * sizeof(char *), 1);
	while (line)
	{
		if (g_global == 1)
		{
			*ret = return_from_sigint(line, args, term, s_env);
			return (NULL);
		}
		if (!ft_strcmp(line, final))
			break ;
		add_to_args_free(&args, line);
		line = next_line(s_env);
		if (!line)
			signal(SIGINT, sigint_handler_nonl);
	}
	free(line);
	*ret = 0;
	return (args);
}

static int	ft_redir_args(char **args, t_env *s_env, int term)
{
	int		pipefd[2];
	int		i;

	if (pipe(pipefd) < 0)
		perror("Pipe: ");
	i = 0;
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (ft_redir_error("dup2", "", s_env));
	while (args[i])
	{
		ft_putstr_fd(args[i], pipefd[1]);
		i++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	ft_free_ptr_array((void **)args);
	if (isatty(term) && dup2(term, STDOUT_FILENO) < 0)
		return (ft_redir_error("dup2", "", s_env));
	return (0);
}
