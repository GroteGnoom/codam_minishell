/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:14:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/16 11:33:51 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "Libft/libft.h"
#include <stdio.h>
#include "minishell.h"

#define SPECIAL_CHARS " \"'|<>"

int	skip_until(char **s, char c)
{
	int	i;

	i = 1;
	while ((*s)[i] && (*s)[i] != c)
		i++;
	i++;
	(*s) += i;
	return (i);
}

int	skip(char **s, char c)
{
	int	i;

	i = 0;
	while ((*s)[i] == c)
		i++;
	(*s) += i;
	return (i);
}

static int	ft_count_parts(char *s)
{
	int		w;
	char	*specials;

	specials = "<>|";
	w = 0;
	while (*s)
	{
		w++;
		if (*s == '"')
			skip_until(&s, '"');
		else if (*s == '\'')
			skip_until(&s, '\'');
		else if (*s == ' ')
			skip(&s, ' ');
		else if (ft_strchr(specials, *s))
			skip(&s, *s);
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
	else if (*s == ' ')
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
		return (skip(&s, *s));
	return (skip_until(&s, *s));
}

t_part	*quote_split(char *s)
{
	int		nr_parts;
	int		i;
	int		len;
	t_part	*parts;

	nr_parts = ft_count_parts(s);
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

t_part	*ft_shell_split(char *s, int last_exit_status, t_env *s_env)
{
	t_part	*parts;
	t_part	*outparts;
	int		i;
	int		j;

	parts = quote_split(s);
	expand_unquoted_args(parts, last_exit_status, s_env);
	expand_wildcard(parts);
	i = 0;
	j = 1;
	while (parts[i].part)
	{
		if (parts[i].type == SPACES && !(parts[i + 1].part && \
		parts[i + 1].type == SPECIAL) && !(i > 0 && \
		parts[i - 1].type == SPECIAL))
			j++;
		if (parts[i].type == SPECIAL)
			j += 2;
		i++;
	}
	outparts = ft_calloc((j + 1) * sizeof(*outparts), 1);
	i = 0;
	j = -1;
	while (parts[i].part)
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
			parts[i - 1].type == SPECIAL))
				outparts[++j].part = ft_calloc(1, 1);
			outparts[j].type = NORMAL;
			ft_strjoin_free(&(outparts[j].part), parts[i].part);
		}
		i++;
	}
	ft_free_parts(parts);
	return (outparts);
}

void	ft_free_parts(t_part *parts)
{
	int	i;

	i = 0;
	while (parts[i].part)
	{
		free(parts[i].part);
		i++;
	}
	free(parts);
}
