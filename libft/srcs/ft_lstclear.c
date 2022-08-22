#include "./libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nodclear;

	while (*lst && del)
	{
		nodclear = *lst;
		*lst = (*lst)->next;
		del(nodclear->content);
		free(nodclear);
	}
}
