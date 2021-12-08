#include "minishell.h"
#include "Libft/libft.h"
int	ft_pwd(int print)
{
	char	*buf;
	char	*print_str;

	buf = NULL;
	print_str = getcwd(buf, 1000);
	free(buf);
	if (print == 1)
	{
		if (write(1, print_str, ft_strlen(print_str)) < 0)
			return (1);
		if (write(1, "\n", 1) < 0)
			return (1);
	}
	return (0);
}
