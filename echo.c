#include "minishell.h"
#include "Libft/libft.h"
int	ft_echo(char **args, int nr_args)
{
	int	i;

	i = 1;
	if (!ft_strcmp(args[i], "-n"))
		i++;
	while (i < nr_args)
	{
		if (write(1, args[i], ft_strlen(args[i])) < 0)
			return (1);
		if (i < nr_args - 1)
		{
			if (write(1, " ", 1) < 0)
				return (1);
		}
		i++;
	}
	if (ft_strcmp(args[1], "-n"))
	{
		if (write(1, "\n", 1) < 0)
			return (1);
	}
	return (0);
}
