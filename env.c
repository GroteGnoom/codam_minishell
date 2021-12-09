#include "Libft/libft.h"
//the env command should only show variables with a value,
//the export command shows everything, and alphabetically
//_=/usr/bin/env should be at the end
void	ft_env(char **envp) //the order is not the same as bash
{
	while (*envp)
	{
		ft_putstr_fd(*envp, 1);
		ft_putchar_fd('\n', 1);
		envp++;
	}
}
