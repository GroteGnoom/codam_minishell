#include "minishell.h"
#include "Libft/libft.h"
#include <termios.h>
#include <stdio.h>
static int	export_attribute(t_env *s_env, char *attr);

static void	ft_free(t_env *s_env);

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
	while (!env_str && i < s_env->size)
	{
		env_str = ft_strnstr(s_env->env[i], env, ft_strlen(s_env->env[i]));
		i++;
	}
	if (i == s_env->size)
		return (export_attribute(s_env, args[1]));
	s_env->env[i - 1] = args[1];
	return (0);
}

void	copy_env(char **envp, t_env *s_env)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	s_env->env = ft_calloc((i + 1) * sizeof(char *), 1);
	s_env->size = i;
	i = 0;
	while (envp[i])
	{
		s_env->env[i] = ft_strdup(envp[i]);
		i++;
	}
}

static int	export_attribute(t_env *s_env, char *attr)
{
	int		i;
	char	**copy;

	i = 0;
	while (s_env->env[i])
		i++;
	if (i == s_env->size)
	{
		copy = ft_calloc((s_env->size + 11) * sizeof(char *), 1);
		i = 0;
		while (s_env->env[i])
		{
			copy[i] = ft_calloc(ft_strlen(s_env->env[i]) + 1, 1);
			ft_memcpy(copy[i], s_env->env[i], ft_strlen(s_env->env[i]));
			i++;
		}
		ft_free(s_env);
		s_env->env = copy;
		s_env->size += 10;
	}
	s_env->env[i] = ft_calloc(ft_strlen(attr) + 1, 1);
	ft_memmove(s_env->env[i], attr, ft_strlen(attr));
	return (0);
}

static void	ft_free(t_env *s_env)
{
	int	i;

	i = 0;
	while (s_env->env[i])
	{
		free(s_env->env[i]);
		i++;
	}
	free(s_env->env);
}
