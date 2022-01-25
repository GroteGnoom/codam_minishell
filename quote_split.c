/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:14:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/25 10:22:55 by dnoom         ########   odam.nl         */
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

void	ft_expand_args(char **s, int last_exit_status, t_env *s_env)
{
	int		i;
	int		is_single_quoted;
	int		is_double_quoted;
	int		envlen;
	char	*env;

	i = 0;
	is_single_quoted = 0;
	is_double_quoted = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'' && !is_double_quoted)
			is_single_quoted = !is_single_quoted;
		else if ((*s)[i] == '"' && !is_single_quoted)
			is_double_quoted = !is_double_quoted;
		else if ((*s)[i] == '$' && !is_single_quoted)
		{
			i++;
			if (ft_insert_exit_status(s, i, last_exit_status))
				continue ;
			envlen = get_env_name_length((*s) + i);
			if (envlen == 0 && (((*s)[i] != '\'' && (*s)[i] != '"')
					|| (is_double_quoted && (*s)[i] == '"')
					|| (is_single_quoted && (*s)[i] == '\'')))
				continue ;
			env = ft_search_name(s_env, *s + i, envlen);
			if (!env)
				env = "";
			ft_replace(s, --i, envlen + 1, env);
			i--;
		}
		i++;
	}
}

t_part	*quote_split(char *s)
{
	int		nr_parts;
	int		i;
	int		j;
	int		len;
	t_part	*parts;

	nr_parts = ft_count_parts_in_str(s);
	parts = ft_calloc((nr_parts + 1) * sizeof(*parts), 1);
	i = 0;
	j = 0;
	while (i < nr_parts)
	{
		len = part_len_type(s + j, &(parts[i].type));
		parts[i].part = ft_calloc((len + 1) * sizeof(char), 1);
		if (parts[i].type == NORMAL || parts[i].type == SPACES
			|| parts[i].type == SPECIAL)
			ft_memcpy(parts[i].part, s + j, len);
		else
			ft_memcpy(parts[i].part, s + j + 1, len - 2);
		j += len;
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
