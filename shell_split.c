/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 11:47:17 by dnoom         #+#    #+#                 */
/*   Updated: 2021/12/16 16:28:16 by dnoom         ########   odam.nl         */
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

int	combine_parts(t_part *parts, t_part *outparts, int i, int j)
{
	if (parts[i].type == SPECIAL)
	{
		outparts[++j].part = ft_calloc(1, 1);
		ft_strjoin_free(&(outparts[j].part), parts[i].part);
		outparts[j].type = SPECIAL;
	}
	else if (parts[i].type != SPACES)
	{
		if (i == 0 || (parts[i - 1].type == SPACES || \
				(parts[i - 1].type == NORMAL && parts[i].type == NORMAL) || \
				parts[i - 1].type == SPECIAL))
			outparts[++j].part = ft_calloc(1, 1);
		outparts[j].type = NORMAL;
		ft_strjoin_free(&(outparts[j].part), parts[i].part);
	}
	return (j);
}

t_part	*ft_shell_split(char *s, int last_exit_status, t_env *s_env)
{
	t_part	*parts;
	t_part	*outparts;
	int		i;
	int		j;

	parts = quote_split(s);
	expand_unquoted_args(parts, last_exit_status, s_env);
	expand_wildcard(&parts);
	outparts = ft_calloc((count_combined_parts(parts) + 1)
			* sizeof(*outparts), 1);
	i = 0;
	j = -1;
	while (parts[i].part)
	{
		j = combine_parts(parts, outparts, i, j);
		i++;
	}
	ft_free_parts(parts);
	return (outparts);
}
