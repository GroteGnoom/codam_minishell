#include "minishell.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
int	ft_redirect_in(char **args, t_env *s_env, int argc)
{
	char	**new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	fd = open(args[argc - 1], O_RDONLY);
	term = 1;
	if (dup2(STDIN_FILENO, term) < 0)
		return (1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (1);
	new_args = ft_calloc((argc - 1) * sizeof(char *), 1);
	i = 0;
	while (ft_strcmp(args[i], "<") != 0)
	{
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	ret = ft_executable(new_args, s_env);
	if (dup2(term, STDIN_FILENO) < 0)
		return (1);
	return (ret);
}

int	ft_redirect_out(char **args, t_env *s_env, int argc)
{
	char	**new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	fd = open(args[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	term = 0;
	if (dup2(STDOUT_FILENO, term) < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	new_args = ft_calloc((argc - 1) * sizeof(char *), 1);
	i = 0;
	while (ft_strcmp(args[i], ">") != 0)
	{
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	ret = ft_executable(new_args, s_env);
	if (dup2(term, STDOUT_FILENO) < 0)
		return (1);
	return (ret);
}

int	ft_redirect_out_app(char **args, t_env *s_env, int argc)
{
	char	**new_args;
	int		ret;
	int		term;
	int		fd;
	int		i;

	fd = open(args[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	term = 0;
	if (dup2(STDOUT_FILENO, term) < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	new_args = ft_calloc((argc - 1) * sizeof(char *), 1);
	i = 0;
	while (ft_strcmp(args[i], ">>") != 0)
	{
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	ret = ft_executable(new_args, s_env);
	if (dup2(term, STDOUT_FILENO) < 0)
		return (1);
	return (ret);
}
