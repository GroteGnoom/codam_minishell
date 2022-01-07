/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/06 13:29:39 by daniel        #+#    #+#                 */
/*   Updated: 2022/01/07 14:56:24 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include "Libft/libft.h"

char	**get_commands_between_pipes(t_part *parts, t_pipe pipex, \
t_env *s_env)
{
	char		**cmd;
	int			i;
	int			j;

	i = 0;
	j = 0;
	cmd = ft_calloc((pipex.len + 1) * sizeof(char *), 1);
	while (parts[i].part && i < pipex.len && !is_pipe(parts[i]))
	{
		if (ft_is_redir(parts[i]))
		{
			if (open(parts[i + 1].part, O_RDONLY) < 0)
			{
				ft_redir_error(SHELL_NAME, parts[i + 1].part, s_env->line_nr);
				exit(0);
			}
			i += 2;
		}
		else
			cmd[j++] = ft_strdup(parts[i++].part);
	}
	return (cmd);
}
