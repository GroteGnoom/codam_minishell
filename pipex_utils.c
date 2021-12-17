/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:13 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/17 10:14:31 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char	**ft_get_commands_parts(int nr_parts, t_part *parts, t_pipe *pipex)
{
	char	**commands;
	int		i;
	int		j;

	i = 0;
	j = 0;
	commands = ft_calloc((nr_parts + 1) * sizeof(char *), 1);
	while (j < nr_parts)
	{
		commands[j] = ft_strdup(parts[i].part);
		i++;
		j++;
	}
	pipex->len = j + pipex->begin - pipex->end;
	return (commands);
}

char	**ft_get_commands(char **argv, int len, t_pipe *pipex)
{
	char	**commands;
	int		i;
	int		j;

	i = 0;
	j = 0;
	commands = ft_calloc((len + 1) * sizeof(char *), 1);
	while (j < len)
	{
		commands[j] = argv[i];
		i++;
		j++;
	}
	pipex->len = j + pipex->begin - pipex->end;
	return (commands);
}

void	ft_close_all_pipes(t_pipe pipex, int *pipefd)
{
	int	i;

	i = 0;
	while (i < (2 * (pipex.size - 1)))
	{
		close(pipefd[i]);
		i++;
	}
	free(pipefd);
}

t_pipe	ft_set_io(int nr_parts, t_part *parts, t_pipe pipex)
{
	if (parts[0].type == SPECIAL && !ft_strcmp(parts[0].part, "<"))
	{
		pipex.infile = open(parts[1].part, O_RDONLY);
		pipex.begin = 2;
	}
	else
		pipex.infile = STDIN_FILENO;
	if (parts[nr_parts - 2].type == SPECIAL && \
	!ft_strcmp(parts[nr_parts - 2].part, ">"))
	{
		pipex.outfile = open(parts[nr_parts - 1].part, \
		O_RDWR | O_CREAT | O_TRUNC, 0644);
		pipex.end = 2;
	}
	else
		pipex.outfile = STDOUT_FILENO;
	return (pipex);
}

t_pipe	ft_get_pipes(t_pipe pipex, int *pipefd)
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
