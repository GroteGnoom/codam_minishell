#include "minishell.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
static void	ft_dup2(int first, int second);

static void	ft_try_paths(t_pipe pipex, char **envp);

static char	**ft_get_cmd_flag(char **commands, int iter, t_pipe pipex);

void	ft_child_process(t_pipe pipex, int *pipefd, char **envp)
{
	if (pipex.iter == 0)
	{
		printf("pipefd[1] = %i\ninfile = %i\niter = %i\n", pipefd[1], pipex.infile, pipex.iter);
		ft_dup2(pipex.infile, pipefd[1]);
	}
	else if (pipex.iter == pipex.size - 1)
	{
		printf("pipefd[0] = %i\noutfile = %i\niter = %i\n", pipefd[2 * pipex.iter - 2], pipex.outfile, pipex.iter);
		ft_dup2(pipefd[2 * pipex.iter - 2], pipex.outfile);
	}
	else
		ft_dup2(pipefd[2 * pipex.iter - 2], pipefd[2 * pipex.iter + 1]);
	ft_close_pipes(pipex, pipefd);
	ft_try_paths(pipex, envp);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(pipex.cmd_flag[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

static void	ft_dup2(int first, int second)
{
	printf("first = %i\nsecond = %i\n\n", first, second);
	if (dup2(first, STDIN_FILENO) < 0)
		perror("dup2");
	if (dup2(second, STDOUT_FILENO) < 0)
		perror("dup2");
}

static void	ft_try_paths(t_pipe pipex, char **envp)
{
	int		i;

	i = 0;
	pipex.cmd_flag = ft_get_cmd_flag(pipex.commands, pipex.iter, pipex);
	while (pipex.paths[i])
	{
		pipex.cmd = ft_strjoin(pipex.paths[i], pipex.cmd_flag[0]);
		if (!access(pipex.cmd, F_OK) && !access(pipex.cmd, X_OK))
			execve(pipex.cmd, pipex.cmd_flag, envp);
		free(pipex.cmd);
		i++;
	}
}

static char	**ft_get_cmd_flag(char **commands, int iter, t_pipe pipex)
{
	char	**cmd;
	int		pipes;
	int		i;
	int		j;

	pipes = 0;
	i = pipex.begin;
	j = 0;
	cmd = ft_calloc((pipex.size + 1) * sizeof(char *), 1);
	while (pipes < iter)
	{
		if (!ft_strcmp(commands[i], "|"))
			pipes++;
		i++;
	}
	while (i < pipex.len - pipex.end && ft_strcmp(commands[i], "|"))
	{
		cmd[j] = ft_strdup(commands[i]);
		i++;
		j++;
	}
	return (cmd);
}
