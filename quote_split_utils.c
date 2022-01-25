/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_split_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dnoom <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 11:24:42 by dnoom         #+#    #+#                 */
/*   Updated: 2022/01/25 11:25:03 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_open_quote(char *s, int is_s_q, int is_d_q)
{
	return ((!is_s_q && s[0] == '\'')
		|| (!is_d_q && s[0] == '"'));
}

int	replace_arg(char **s, int *i, t_env *s_env, int *is_q)
{
	int		envlen;
	char	*env;

	envlen = get_env_name_length((*s) + *i);
	if (envlen == 0 && !next_open_quote((*s) + *i, is_q[1], is_q[2]))
		return (1);
	env = ft_search_name(s_env, *s + *i, envlen);
	ft_replace(s, --(*i), envlen + 1, env);
	return (0);
}
