/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:43 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:15:46 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

static int		ft_pipex_pipe(t_pipe pipe, char **envp);

static t_pipe	ft_get_pipes(t_pipe pipex, int *pipefd);

static int		ft_get_size(char **argv);

int	ft_pipex(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	int		status;

	pipex.begin = 0;
	pipex.end = 0;
	if (!ft_strcmp(argv[0], "<"))
	{
		pipex.infile = open(argv[1], O_RDONLY);
		pipex.begin = 2;
	}
	else
		pipex.infile = STDIN_FILENO;
	if (!ft_strcmp(argv[argc - 2], ">"))
	{
		pipex.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		pipex.end = 2;
	}
	else
		pipex.outfile = STDOUT_FILENO;
	if (pipex.infile < 0 || pipex.outfile < 0)
	{
		perror("bash: input");
		if (pipex.outfile < 0)
			return (127);
		write(pipex.outfile, "       0\n", 9);
		return (0);
	}
	pipex.commands = ft_get_commands(argv, argc, &pipex);
	pipex.size = ft_get_size(argv);
	status = ft_pipex_pipe(pipex, envp);
	return (status);
}

static int	ft_get_size(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "|"))
			count++;
		i++;
	}
	return (count);
}

static int	ft_pipex_pipe(t_pipe pipex, char **envp)
{
	pid_t	child;
	int		*pipefd;
	int		status;

	pipefd = (int *)malloc((2 * (pipex.size - 1)) * sizeof(int));
	if (!pipefd)
		perror("malloc: ");
	pipex = ft_get_pipes(pipex, pipefd);
	pipex.paths = ft_get_paths(envp);
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
	if (pipex.infile != STDIN_FILENO)
		close(pipex.infile);
	if (pipex.outfile != STDOUT_FILENO)
		close(pipex.outfile);
	return (WEXITSTATUS(status));
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
