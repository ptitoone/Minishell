#include "./libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*lastnode;

	newlst = 0;
	if (lst && f && del)
	{
		newlst = ft_lstnew(f(lst->content));
		lastnode = newlst;
		lst = lst->next;
		while (lst && lastnode)
		{
			lastnode->next = ft_lstnew(f(lst->content));
			lastnode = lastnode->next;
			lst = lst->next;
		}
		if (!(lastnode))
			ft_lstclear(&newlst, del);
	}
	return (newlst);
}
