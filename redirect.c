#include "minishell.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
int	ft_redirect_in(char **args, t_env *s_env, int argc)
{
	char	**new_args;
	int		ret;
	int		fd;
	int		i;

	printf("%s\n", args[argc]);
	fd = open(args[argc], O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (1);
	new_args = ft_calloc((argc - 1) * sizeof(char *), 1);
	i = 0;
	while (ft_strcmp(args[i], "<") != 0)
	{
		printf("%s\n", args[i]);
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	ret = ft_executable(new_args, s_env);
	close(fd);
	return (ret);
}
