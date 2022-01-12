/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_special.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/07 09:46:04 by daniel        #+#    #+#                 */
/*   Updated: 2022/01/12 09:46:43 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	ft_is_redir(t_part part)
{
	static char	*redir[] = {"<", "<<", ">>", ">", NULL};
	char		**redir_p;

	if (part.type != SPECIAL)
		return (0);
	redir_p = redir;
	while (*redir_p)
	{
		if (!ft_strcmp(*redir_p, part.part))
			return (1);
		redir_p ++;
	}
	return (0);
}

int	is_pipe(t_part part)
{
	return (!ft_strcmp(part.part, "|") && part.type == SPECIAL);
}

int	is_input_redir(t_part part)
{
	return (!ft_strcmp(part.part, "<") && part.type == SPECIAL);
}

int	is_output_redir(t_part part)
{
	return (!ft_strcmp(part.part, ">") && part.type == SPECIAL);
}

int	is_here_doc(t_part part)
{
	return (!ft_strcmp(part.part, "<<") && part.type == SPECIAL);
}
