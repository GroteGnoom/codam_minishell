#include "minishell.h"
#include "Libft/libft.h"
#include <termios.h>
static int	export_attribute(t_env *s_env, char *attr);

int	ft_export(char **args, t_env *s_env)
{
	char	*env;
	char	*env_str;
	int		i;

	env_str = NULL;
	i = 0;
	env = ft_strchr(args[1], '=');
	if (env != 0)
		env = ft_substr(args[1], 0, ft_strlen(args[1]) - ft_strlen(env));
	else
		return (export_attribute(s_env, args[1]));
	while (!env_str)
	{
		env_str = ft_strnstr(s_env->env[i], env, ft_strlen(s_env->env[i]));
		i++;
	}
	s_env->env[i] = args[1];
	return (0);
}

void	copy_env(char **envp, t_env *s_env)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	s_env->env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		s_env->env[i] = ft_strdup(envp[i]);
		i++;
	}
	s_env->env[i] = NULL;
	s_env->size = i;
}

static int	export_attribute(t_env *s_env, char *attr)
{
	(void)s_env;
	(void)attr;
	return (0);
}
