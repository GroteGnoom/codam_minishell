/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:03 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 10:24:13 by sde-rijk      ########   odam.nl         */
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
	char	*old_pwd;
	char	*print_str;
	int		i;

	i = 0;
	old_pwd = get_prev_var(s_env, "OLDPWD", &i);
	if (old_pwd)
		print_str = ft_strjoin(old_pwd + 7, "\n");
	if (!old_pwd || write(1, print_str, ft_strlen(print_str)) < 0)
		return (1);
	free(print_str);
	return (0);
}

int	ft_pwd(t_env *s_env)
{
	char	*buf;
	char	*print_str;

	buf = NULL;
	print_str = getcwd(buf, PATH_MAX);
	free(buf);
	if (!print_str)
		return (print_old_pwd(s_env));
	if (write(1, print_str, ft_strlen(print_str)) < 0)
		return (1);
	if (write(1, "\n", 1) < 0)
		return (1);
	free(print_str);
	return (0);
}
