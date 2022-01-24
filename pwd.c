/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:03 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 11:32:45 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#ifdef __APPLE__
# include <sys/syslimits.h>
#else
# include <linux/limits.h>
#endif

int	print_old_pwd(t_env *s_env)
{
	char	*pwd;
	char	*print_str;
	int		i;
	int		err;

	i = 0;
	pwd = get_prev_var(s_env, "PWD", &i);
	err = 0;
	if (pwd)
	{
		print_str = ft_strjoin(pwd + 4, "\n");
		if (write(1, print_str, ft_strlen(print_str)) < 0)
			err = 1;
		free(print_str);
		return (err);
	}
	return (1);
}

int	ft_pwd(t_env *s_env)
{
	char	*print_str;
	char	buf[PATH_MAX];

	print_str = getcwd(buf, PATH_MAX);
	if (!print_str)
		return (print_old_pwd(s_env));
	if (write(1, print_str, ft_strlen(print_str)) < 0)
		return (1);
	if (write(1, "\n", 1) < 0)
		return (1);
	return (0);
}
