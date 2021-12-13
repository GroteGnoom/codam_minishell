#include "minishell.h"
#include "Libft/libft.h"
int	ft_executable(char **args, t_env *s_env)
{
	pid_t	child;
	char	**paths;
	int		status;

	paths = ft_get_paths(s_env->env);
	child = fork();
	if (child < 0)
		return (1);
	if (child == 0)
		ft_try_paths(paths, args, s_env->env);
	waitpid(-1, &status, 0);
	return (WEXITSTATUS(status));
}

