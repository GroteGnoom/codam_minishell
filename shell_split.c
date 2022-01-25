/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 11:47:17 by dnoom         #+#    #+#                 */
/*   Updated: 2022/01/25 10:23:13 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int		new_part_required(int i, t_part *parts);
void	add_special_outpart(t_part part, t_part *outparts, int *j,
			int **wild_quoted);
void	set_quotes(t_part part, int j, int length, int **wild_quoted);
void	calloc_2(t_part *outparts, int **wild_quoted, int *j);

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
				calloc_2(outparts, wild_quoted, &j);
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
	int		count;

	s = ft_strdup(s);
	ft_expand_args(&s, last_exit_status, s_env);
	parts = quote_split(s);
	free(s);
	count = count_combined_parts(parts);
	outparts = ft_calloc(count + 1, sizeof(*outparts));
	wild_quoted = ft_calloc(count + 1, sizeof(*wild_quoted));
	combine_parts(parts, outparts, wild_quoted);
	expand_wildcard(&outparts, wild_quoted);
	ft_free_parts(parts);
	ft_free_ptr_array((void **)wild_quoted);
	return (outparts);
}
