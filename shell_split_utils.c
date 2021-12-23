/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_split_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: daniel <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/23 15:05:47 by daniel        #+#    #+#                 */
/*   Updated: 2021/12/23 15:07:22 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	new_part_required(int i, t_part *parts)
{
	return (i == 0 || (parts[i - 1].type == SPACES || \
		(parts[i - 1].type == NORMAL && parts[i].type == NORMAL) || \
		parts[i - 1].type == SPECIAL));
}

void	add_special_outpart(t_part part, t_part *outparts, int *j,
		int **wild_quoted)
{
	outparts[++(*j)].part = ft_calloc(1, 1);
	wild_quoted[(*j)] = ft_calloc(ft_strlen(part.part), sizeof(int));
	ft_strjoin_free(&(outparts[(*j)].part), part.part);
	outparts[(*j)].type = SPECIAL;
}

void	set_quotes(t_part part, int j, int length, int **wild_quoted)
{
	int	k;

	k = 0;
	while (k < (int)ft_strlen(part.part))
		*(wild_quoted[j] + length + k++) = (part.type == SINGLE_QUOTED
				|| part.type == DOUBLE_QUOTED);
}

void	calloc_2(t_part *outparts, int **wild_quoted, int *j)
{
	outparts[++(*j)].part = ft_calloc(1, 1);
	wild_quoted[(*j)] = ft_calloc(1, sizeof(int));
}
