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
static int		ft_get_size_parts(t_part *parts);

int	ft_pipex(int nr_parts, t_part *parts, char **envp)
{
	t_pipe	pipex;
	int		status;

	pipex.begin = 0;
	pipex.end = 0;
	if (parts[0].type == SPECIAL && !ft_strcmp(parts[0].part, "<"))
	{
		pipex.infile = open(parts[0].part, O_RDONLY);
		pipex.begin = 2;
	}
	else
		pipex.infile = STDIN_FILENO;
	if (parts[0].type == SPECIAL && !ft_strcmp(parts[nr_parts - 2].part, ">"))
	{
		pipex.outfile = open(parts[nr_parts -1].part, O_RDWR | O_CREAT | O_TRUNC, 0644);
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
	pipex.commands = ft_get_commands_parts(nr_parts, parts, &pipex);
	pipex.size = ft_get_size_parts(parts);
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

static int	ft_get_size_parts(t_part *parts)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (parts[i].part)
	{
		if (parts[i].type == SPECIAL && !ft_strcmp(parts[i].part, "|"))
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
