/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:16:00 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"

void	ft_try_paths(char **paths, char **args, char **envp)
{
	char	*cmd;
	int		i;
	int		relative;

	i = 0;
	while (paths[i])
	{
		relative = !ft_strchr(args[0], '/');
		if (relative)
			cmd = ft_strjoin(paths[i], args[0]);
		else
			cmd = args[0];
		if (!access(cmd, F_OK) && !access(cmd, X_OK))
			execve(cmd, args, envp);
		if (relative)
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
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}