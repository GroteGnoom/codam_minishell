/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/06 13:29:39 by daniel        #+#    #+#                 */
/*   Updated: 2022/01/06 14:11:25 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include "Libft/libft.h"

char	**get_commands_between_pipes(t_part *parts, t_pipe pipex, \
t_env *s_env, char **commands)
{
	char		**cmd;
	int			i;
	int			j;
	static char	*redir[] = {"<", ">>", ">", NULL};

	i = 0;
	j = 0;
	cmd = ft_calloc((pipex.len + 1) * sizeof(char *), 1);
	while (commands[i] && i < pipex.len && (ft_strcmp(commands[i], "|") \
	|| parts[i].type != SPECIAL))
	{
		if (!ft_strcmp_multi(commands[i], redir))
		{
			if (open(commands[i + 1], O_RDONLY) < 0)
			{
				ft_redir_error(SHELL_NAME, commands[i + 1], s_env->line_nr);
				exit(0);
			}
			i += 2;
		}
		else
			cmd[j++] = ft_strdup(commands[i++]);
	}
	return (cmd);
}
