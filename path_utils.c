/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/15 14:06:31 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

void	ft_try_paths(char **paths, char **args, t_env *s_env, t_part *parts)
{
	char	*cmd;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (!ft_strcmp(args[0], "export"))
		{
			ft_export(parts, s_env);
			exit(0);
		}
		if (!ft_strchr(args[0], '/'))
			cmd = ft_strjoin(paths[i], args[0]);
		else
			cmd = args[0];
		if (!access(cmd, F_OK) && !access(cmd, X_OK))
			execve(cmd, args, s_env->env);
		if (!ft_strchr(args[0], '/'))
			free(cmd);
		i++;
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

char	**ft_get_paths(char **env)
{
	char	**paths;
	char	*path;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (!line)
	{
		line = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	path = ft_substr(line, 5, ft_strlen(line));
	paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (paths[i])
	{
		ft_strjoin_free(&paths[i], "/");
		i++;
	}
	return (paths);
}
