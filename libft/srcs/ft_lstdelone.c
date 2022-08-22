#include "./libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*noddel;

	if (lst && del)
	{
		noddel = lst;
		lst = lst->next;
		del(noddel->content);
		free(noddel);
	}
}
