#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"

int	is_int(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_exit(char **args, int nr_args)
{
	if (nr_args == 1)
		exit(0);
	if (!is_int(args[1]))
	{
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}
	if (nr_args > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else
		exit(ft_atoi(args[1]));
}
