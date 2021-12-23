/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 11:47:17 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/23 14:58:53 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	count_combined_parts(t_part *parts)
{
	int		i;
	int		j;

	j = 1;
	i = 0;
	while (parts[i].part)
	{
		if (parts[i].type == SPACES && !(parts[i + 1].part && \
		parts[i + 1].type == SPECIAL) && !(i > 0 && \
		parts[i - 1].type == SPECIAL))
			j++;
		if (parts[i].type == SPECIAL)
			j += 2;
		if (i != 0 && parts[i].type == NORMAL && parts[i - 1].type == NORMAL)
			j += 2;
		i++;
	}
	return (j);
}

int	new_part_required(int i, t_part *parts)
{
	return (i == 0 || (parts[i - 1].type == SPACES || \
		(parts[i - 1].type == NORMAL && parts[i].type == NORMAL) || \
		parts[i - 1].type == SPECIAL));
}

void	add_special_outpart(t_part part, t_part *outparts, int *j, int **wild_quoted)
{
	outparts[++(*j)].part = ft_calloc(1, 1);
	wild_quoted[(*j)] = ft_calloc(ft_strlen(part.part), sizeof(int));
	ft_strjoin_free(&(outparts[(*j)].part), part.part);
	outparts[(*j)].type = SPECIAL;
}

void	set_quotes(t_part part, int j, int length, int **wild_quoted) 
{
	int k;

	k = 0;
	while (k < (int)ft_strlen(part.part))
		*(wild_quoted[j] + length + k++) = (part.type == SINGLE_QUOTED
				|| part.type == DOUBLE_QUOTED);
}

void	combine_parts(t_part *parts, t_part *outparts, int **wild_quoted)
{
	int	length;
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (parts[i].part)
	{
		if (parts[i].type == SPECIAL)
			add_special_outpart(parts[i], outparts, &j, wild_quoted);
		else if (parts[i].type != SPACES)
		{
			if (new_part_required(i, parts))
			{
				outparts[++j].part = ft_calloc(1, 1);
				wild_quoted[j] = ft_calloc(1, sizeof(int));
			}
			outparts[j].type = NORMAL;
			length = ft_strlen(outparts[j].part);
			wild_quoted[j] = ft_realloc(wild_quoted[j], (length + \
				ft_strlen(parts[i].part)) * sizeof(int), length * sizeof(int));
			ft_strjoin_free(&(outparts[j].part), parts[i].part);
			set_quotes(parts[i], j, length, wild_quoted);
		}
		i++;
	}
}

t_part	*ft_shell_split(char *s, int last_exit_status, t_env *s_env)
	{
		t_part	*parts;
		t_part	*outparts;
		int		**wild_quoted;

	parts = quote_split(s);
	expand_unquoted_args(parts, last_exit_status, s_env);
	outparts = ft_calloc((count_combined_parts(parts) + 1)
			* sizeof(*outparts), 1);
	wild_quoted = ft_calloc((count_combined_parts(parts) + 1)
			* sizeof(*wild_quoted), 1);
	combine_parts(parts, outparts, wild_quoted);
	expand_wildcard(&outparts, wild_quoted);
	ft_free_parts(parts);
	ft_free_strs((char **)wild_quoted);
	return (outparts);
}
