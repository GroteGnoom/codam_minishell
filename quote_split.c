/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:14:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/07 14:21:59 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "Libft/libft.h"
#include <stdio.h>
#include "minishell.h"

#define SPECIAL_CHARS " \"'|<>\n"

static int	ft_count_parts_in_str(char *s)
{
	int		w;
	char	*specials;

	specials = "<>|";
	w = 0;
	while (*s)
	{
		w++;
		if (*s == '"')
			ft_skip_until(&s, '"');
		else if (*s == '\'')
			ft_skip_until(&s, '\'');
		else if (*s == ' ')
			ft_skip(&s, ' ');
		else if (*s == '\n')
			ft_skip(&s, '\n');
		else if (ft_strchr(specials, *s))
			ft_skip(&s, *s);
		else
			while (*s && !ft_strchr(SPECIAL_CHARS, *s))
				s++;
	}
	return (w);
}

int	part_len_type(char *s, enum e_part_type *type)
{
	int		i;
	char	*specials;

	specials = "<>|";
	i = 0;
	*type = NORMAL;
	if (*s == '"')
		*type = DOUBLE_QUOTED;
	else if (*s == '\'')
		*type = SINGLE_QUOTED;
	else if (*s == ' ' || *s == '\n')
		*type = SPACES;
	else if (ft_strchr(specials, *s))
		*type = SPECIAL;
	else
	{
		while (s[i] && !ft_strchr(SPECIAL_CHARS, s[i]))
			i++;
		return (i);
	}
	if (*type == SPACES || *type == SPECIAL)
		return (ft_skip(&s, *s));
	return (ft_skip_until(&s, *s));
}

t_part	*quote_split(char *s)
{
	int		nr_parts;
	int		i;
	int		len;
	t_part	*parts;

	nr_parts = ft_count_parts_in_str(s);
	parts = ft_calloc((nr_parts + 1) * sizeof(*parts), 1);
	i = 0;
	while (i < nr_parts)
	{
		len = part_len_type(s, &(parts[i].type));
		parts[i].part = ft_calloc((len + 1) * sizeof(char), 1);
		if (parts[i].type == NORMAL || parts[i].type == SPACES
			|| parts[i].type == SPECIAL)
			ft_memcpy(parts[i].part, s, len);
		else
			ft_memcpy(parts[i].part, s + 1, len - 2);
		s += len;
		i++;
	}
	return (parts);
}

void	ft_free_parts(t_part *parts)
{
	int	i;

	i = 0;
	if (!parts)
		return ;
	while (parts[i].part)
	{
		free(parts[i].part);
		i++;
	}
	free(parts);
}
