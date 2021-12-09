#include "Libft/libft.h"
#include "stdio.h"

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
	char	*les;

	s = *sp;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
			{
				les = ft_itoa(last_exit_status);
				ft_replace(sp, i - 1, 2, les);
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
