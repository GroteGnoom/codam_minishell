/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:40 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 14:46:25 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

static char	**ft_get_args(int nr_parts, t_part *parts);

int	ft_executable(int nr_parts, t_part *parts, t_env *s_env)
{
	pid_t	child;
	char	**args;
	char	**paths;
	int		status;
	sig_t	old_signal[2];

	paths = ft_get_paths(s_env->env);
	args = ft_get_args(nr_parts, parts);
	old_signal[0] = signal(SIGINT, sigint_handler_in_process);
	old_signal[1] = signal(SIGQUIT, sigquit_handler_in_process);
	child = fork();
	if (child < 0)
	{
		perror("Fork: ");
		return (1);
	}
	if (child == 0)
		ft_try_paths(paths, args, s_env);
	waitpid(-1, &status, 0);
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
	ft_free_ptr_array((void **)paths);
	ft_free_ptr_array((void **)args);
	return (WEXITSTATUS(status));
}

static char	**ft_get_args(int nr_parts, t_part *parts)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_calloc((nr_parts + 1) * sizeof(char *), 1);
	while (i < nr_parts)
	{
		args[i] = ft_strdup(parts->part);
		parts++;
		i++;
	}
	return (args);
}
