#include "Libft/libft.h"
#include "stdio.h"
#include "minishell.h"

void	ft_replace(char **sp, int start, int len, char *rep)
{
	char	*new;

	new = malloc(ft_strlen(*sp) + ft_strlen(rep) - len);
	ft_memcpy(new, *sp, start);
	ft_memcpy(new + start, rep, ft_strlen(rep));
	ft_memcpy(new + start + ft_strlen(rep), *sp + start + len,
		ft_strlen(*sp) - start);
	free(*sp);
	*sp = new;
}

void	expand_args(char **sp, int last_exit_status)
{
	char	*s;
	int		i;
	char	*envname;
	char	*env;
	int		envlen;

	s = *sp;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
			{
				env = ft_itoa(last_exit_status);
				ft_replace(sp, i - 1, 2, env);
				continue ;
			}
			envlen = 0;
			while (s[i + envlen] && s[i + envlen] != ' ')
				envlen++;
			envname = ft_substr(s, i, envlen);
			env = getenv(envname);
			if (env)
				ft_replace(sp, i - 1, envlen + 1, env);
			s = *sp;
		}
		i++;
	}
}

void	expand_unquoted_args(t_part *parts, int last_exit_status)
{
	while (parts->part)
	{
		if (parts->type == NORMAL || parts->type == DOUBLE_QUOTED)
			expand_args(&(parts->part), last_exit_status);
		parts++;
	}
}
