#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
static int		ft_pipex(t_pipe pipe, char **envp);

static t_pipe	ft_get_data(t_pipe pipex, char **envp);

static t_pipe	ft_get_pipes(t_pipe pipex, int *pipefd);

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	int		status;

	if (argc < 5)
		perror("Not enough arguments:");
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
	{
		perror("bash: input");
		if (pipex.outfile < 0)
			exit(127);
		write(pipex.outfile, "       0\n", 9);
		return (0);
	}
	if (!*envp)
	{
		write(pipex.outfile, "       1\n", 9);
		exit(0);
	}
	pipex.commands = ft_get_commands(argv, argc - 3);
	pipex.size = argc - 3;
	status = ft_pipex(pipex, envp);
	return (status);
}

static int	ft_pipex(t_pipe pipex, char **envp)
{
	pid_t	child;
	int		*pipefd;
	int		status;

	pipefd = (int *)malloc((2 * (pipex.size - 1)) * sizeof(int));
	if (!pipefd)
		perror("malloc: ");
	pipex = ft_get_pipes(pipex, pipefd);
	pipex = ft_get_data(pipex, envp);
	pipex.iter = 0;
	while (pipex.iter < pipex.size)
	{
		child = fork();
		if (child < 0)
			perror("Fork: ");
		if (child == 0)
			ft_child_process(pipex, pipefd, envp);
		pipex.iter++;
	}
	ft_close_pipes(pipex, pipefd);
	waitpid(-1, &status, 0);
	close(pipex.infile);
	close(pipex.outfile);
	return (WEXITSTATUS(status));
}

static t_pipe	ft_get_data(t_pipe pipex, char **envp)
{
	char	*path;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (!line)
	{
		line = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	path = ft_substr(line, 5, ft_strlen(line));
	pipex.paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (pipex.paths[i])
	{
		pipex.paths[i] = ft_strjoin(pipex.paths[i], "/");
		i++;
	}
	return (pipex);
}

static t_pipe	ft_get_pipes(t_pipe pipex, int *pipefd)
{
	int	i;

	i = 0;
	while (i < pipex.size - 1)
	{
		if (pipe(pipefd + 2 * i) < 0)
			perror("Pipe: ");
		i++;
	}
	return (pipex);
}
