#include "Libft/libft.h"
void	ft_try_paths(char **paths, char **args, char **envp)
{
	char	*cmd;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (!ft_strchr(args[0], '/'))
			cmd = ft_strjoin(paths[i], args[0]);
		else
			cmd = args[0];
		if (!access(cmd, F_OK) && !access(cmd, X_OK))
			execve(cmd, args, envp);
		free(cmd);
		i++;
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
