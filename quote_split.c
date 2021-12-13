/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:14:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:14:59 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "Libft/libft.h"
#include <stdio.h>
#include "minishell.h"

#define SPECIAL_CHARS " \"'|"

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
		else if (*s == '|') //todo: others
			s++;
		else
			while (*s && !ft_strchr(SPECIAL_CHARS, *s))
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
	else if (*s == '|')
	{
		*type = SPECIAL;
		return (skip(&s, '|')); //TODO only works for one pipe
	}
	else
		while (s[i] && !ft_strchr(SPECIAL_CHARS, s[i]))
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


/* we should not lose the information about wheter >'s are quoted or not
 * ">" is not a redirection */
char	**ft_shell_split_bad(char *s)
{
	t_part	*parts;
	char	**pipe_parts;
	int		i;
	int		j;

	parts = quote_split(s);
	//expand args should be here
	i = 0;
	j = 0;
	while (parts[i].part)
	{
		if (parts[i].type == SPECIAL)
			j++;
		i++;
	}
	pipe_parts = malloc((j + 1) * sizeof(char **));
	pipe_parts[0] = malloc(1);
	pipe_parts[0][0] = 0;
	i = 0;
	j = 0;
	while (parts[i].part)
	{
		if (parts[i].type == SPECIAL)
		{
			j++;
			pipe_parts[j] = malloc(1);
			pipe_parts[j][0] = 0;
		}
		else
		{
			ft_strjoin_free(&(pipe_parts[j]), parts[i].part);
		}
		i++;
	}
	return (pipe_parts);
}


t_part *ft_shell_split(char *s)
{
	t_part	*parts;
	t_part	*outparts;
	int		i;
	int		j;

	parts = quote_split(s);
	expand_unquoted_args(parts, 0);
	i = 0;
	j = 1;
	while (parts[i].part)
	{
		if (parts[i].type == SPACES)
			j++;
		if (parts[i].type == SPECIAL)
			j += 2;
		i++;
	}
	printf("number of total parts: %d\n", i);
	outparts = malloc((j + 1) * sizeof(*outparts));
	outparts[j].part = NULL;
	outparts[0].part = malloc(1);
	outparts[0].part[0] = 0;
	i = 0;
	j = 0;
	while (parts[i].part)
	{
		if (parts[i].type == SPACES)
		{
			if (i != 0 && outparts[j - 1].type != SPECIAL)
			{
				j++;
				outparts[j].part = malloc(1);
				outparts[j].part[0] = 0;
			}
		}
		else if (parts[i].type == SPECIAL)
		{
			if (i != 0 && outparts[j].part[0] != 0)
			{
				j++;
				outparts[j].part = malloc(1);
				outparts[j].part[0] = 0;
			}
			ft_strjoin_free(&(outparts[j].part), parts[i].part);
			outparts[j].type = SPECIAL;
			j++;
			outparts[j].part = malloc(1);
			outparts[j].part[0] = 0;
		}
		else
		{
			outparts[j].type = NORMAL;
			ft_strjoin_free(&(outparts[j].part), parts[i].part);
		}
		i++;
	}
	return (outparts);
}

