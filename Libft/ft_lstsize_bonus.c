#include "libft.h"
int	ft_lstsize(t_list *lst)
{
	t_list	*cpy;
	int		len;

	if (!lst)
		return (0);
	cpy = lst;
	len = 1;
	while (cpy->next != 0)
	{
		cpy = cpy->next;
		len++;
	}
	return (len);
}
