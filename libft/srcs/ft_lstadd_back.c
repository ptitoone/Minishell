#include "./libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (new)
	{
		if (!(*alst))
			*alst = new;
		else
			ft_lstlast(*alst)->next = new;
	}
}
