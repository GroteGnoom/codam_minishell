/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_wildcard.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 15:17:24 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/24 11:27:51 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include "stdio.h"

static int	expand_wild(char **part, int *wild_quoted);

int	count_parts(t_part *s)
{
	int	i;

	i = 0;
	while (s[i].part)
		i++;
	return (i);
}

int	replace_parts(t_part **parts, int i)
{
	char	**split;
	int		nr_old_parts;
	int		nr_new_parts;
	int		j;
	char	*old;

	nr_old_parts = count_parts(*parts);
	split = ft_split((*parts)[i].part, ' ');
	nr_new_parts = ft_count_strs(split);
	old = (*parts)[i].part;
	*parts = ft_recalloc(*parts,
			(nr_old_parts + nr_new_parts + 1) * sizeof(**parts),
			(nr_old_parts + 1) * sizeof(**parts));
	ft_memmove((*parts) + i + nr_new_parts - 1, (*parts) + i,
		(nr_old_parts - i) * sizeof(**parts));
	j = 0;
	while (j < nr_new_parts)
	{
		(*parts)[i + j].part = split[j];
		(*parts)[i + j].type = NORMAL;
		j++;
	}
	free(split);
	free(old);
	return (nr_new_parts);
}

void	expand_wildcard(t_part **parts, int **wild_quoted)
{
	int		i;

	i = 0;
	while ((*parts)[i].part)
	{
		if ((*parts)[i].type == NORMAL)
		{
			if (expand_wild(&(*parts)[i].part, wild_quoted[i]))
				i += replace_parts(parts, i);
		}
		i++;
	}
}

static int	expand_wild(char **part, int *wild_quoted)
{
	char	*str;
	int		i;

	i = 0;
	str = *part;
	while (str[i])
	{
		if (str[i] == '*')
		{
			*part = ft_wildcard(*part, wild_quoted);
			return (1);
		}
		i++;
	}
	return (0);
}
