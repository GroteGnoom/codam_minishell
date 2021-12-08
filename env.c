#include "Libft/libft.h"
void	ft_env(char **envp) //the order is not the same as bash
{
	while (*envp)
	{
		ft_putstr_fd(*envp, 1);
		ft_putchar_fd('\n', 1);
		envp++;
	}
}
