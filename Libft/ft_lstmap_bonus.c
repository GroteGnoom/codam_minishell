#include "libft.h"
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_lst;

	new_lst = 0;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (new == 0)
		{
			while (new_lst != 0)
			{
				new = new_lst->next;
				(*del)(new_lst->content);
				free(new_lst);
				new_lst = new;
			}
			lst = 0;
			return (0);
		}
		ft_lstadd_back(&new_lst, new);
		lst = lst->next;
	}
	return (new_lst);
}
