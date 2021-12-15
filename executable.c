/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:40 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/15 09:29:16 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

static char	**ft_get_args(int nr_parts, t_part *parts);

int	ft_executable(int nr_parts, t_part *parts, t_env *s_env)
{
	pid_t	child;
	char	**args;
	char	**paths;
	int		status;

	paths = ft_get_paths(s_env->env);
	args = ft_get_args(nr_parts, parts);
	child = fork();
	if (child < 0)
		return (1); //is this the correct error handling?
	if (child == 0)
		ft_try_paths(paths, args, s_env->env);
	waitpid(-1, &status, 0);
	ft_free_strs(paths);
	ft_free_strs(args);
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
