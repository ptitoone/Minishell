#include "./libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*lstcpy;
	int		lstsize;

	lstcpy = lst;
	lstsize = 0;
	while (lstcpy)
	{
		lstcpy = lstcpy->next;
		lstsize++;
	}
	return (lstsize);
}
