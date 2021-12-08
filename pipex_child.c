#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
static void	ft_dup2(int first, int second);

static void	ft_try_paths(t_pipe pipex, char **envp);

void	ft_child_process(t_pipe pipex, int *pipefd, char **envp)
{
	if (pipex.iter == 0)
		ft_dup2(pipex.infile, pipefd[1]);
	else if (pipex.iter == pipex.size - 1)
		ft_dup2(pipefd[2 * pipex.iter - 2], pipex.outfile);
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
	if (dup2(first, STDIN_FILENO) < 0)
		perror("dup2");
	if (dup2(second, STDOUT_FILENO) < 0)
		perror("dup2");
}

static void	ft_try_paths(t_pipe pipex, char **envp)
{
	int		i;

	i = 0;
	pipex.cmd_flag = ft_split_commands(pipex.commands[pipex.iter], ' ');
	while (pipex.paths[i])
	{
		pipex.cmd = ft_strjoin(pipex.paths[i], pipex.cmd_flag[0]);
		if (!access(pipex.cmd, F_OK & X_OK))
			execve(pipex.cmd, pipex.cmd_flag, envp);
		free(pipex.cmd);
		i++;
	}
}
