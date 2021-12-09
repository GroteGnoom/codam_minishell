#include "minishell.h"
#include "Libft/libft.h"
static char	**ft_get_data(t_env *s_env);

int	ft_executable(char **args, t_env *s_env)
{
	pid_t	child;
	char	**paths;
	char	*cmd;
	int		status;
	int		i;

	i = 0;
	paths = ft_get_data(s_env);
	child = fork();
	if (child < 0)
		return (1);
	if (child == 0)
	{
		while (paths[i])
		{
			cmd = ft_strjoin(paths[i], args[0]);
			if (!access(cmd, F_OK & X_OK))
				execve(cmd, args, s_env->env);
			free(cmd);
			i++;
		}
	}
	waitpid(-1, &status, 0);
	return (0);
}

static char	**ft_get_data(t_env *s_env)
{
	char	**paths;
	char	*path;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (!line)
	{
		line = ft_strnstr(s_env->env[i], "PATH=", 5);
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
