#include <stdlib.h>
#include "Libft/libft.h"
#include <stdio.h>
#include "minishell.h"

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
	int	w;

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
		else
			while (*s && *s != '"' && *s != '\'' && *s != ' ')
				s++;
	}
	return (w);
}

int	part_len_type(char *s, enum e_part_type *type)
{
	int	i;

	i = 0;
	if (*s == '"')
	{
		*type = DOUBLE_QUOTED;
		return (skip_until(&s, '"'));
	}
	else if (*s == '\'')
	{
		*type = SINGLE_QUOTED;
		return (skip_until(&s, '\''));
	}
	else if (*s == ' ')
	{
		*type = SPACES;
		return (skip(&s, ' '));
	}
	else
		while (s[i] && s[i] != '"' && s[i] != '\'' && s[i] != ' ')
			i++;
	*type = NORMAL;
	return (i);
}

t_part	*quote_split(char *s)
{
	int		nr_parts;
	int		i;
	int		len;
	t_part	*parts;

	nr_parts = ft_count_parts(s);
	parts = malloc((nr_parts + 1) * sizeof(*parts));
	parts[nr_parts].part = NULL;
	i = 0;
	while (i < nr_parts)
	{
		len = part_len_type(s, &(parts[i].type));
		parts[i].part = malloc((len + 1) * sizeof(char));
		parts[i].part[len] = 0;
		if (parts[i].type == NORMAL || parts[i].type == SPACES)
			ft_memcpy(parts[i].part, s, len);
		else
			ft_memcpy(parts[i].part, s + 1, len - 2);
		s += len;
		i++;
	}
	return (parts);
}

char	**parts_to_strings(t_part *parts)
{
	int		n;
	char	**strs;
	int		i;

	n = 0;
	i = 0;
	while (parts[n].part)
		n++;
	strs = malloc(n * sizeof(char *));
	n = 0;
	i = 0;
	while (parts[n].part)
	{
		if (parts[n].type != SPACES)
		{
			strs[i] = parts[n].part;
			i++;
		}
		n++;
	}
	strs[i] = NULL;
	return (strs);
}
