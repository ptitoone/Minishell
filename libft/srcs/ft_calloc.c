#include "./libft.h"

t_ribool	ft_calloc(size_t count, size_t size, void *ptr)
{
	void	*newcal;

	newcal = malloc(count * size);
	if (!(newcal))
		return (T_FALSE);
	ft_bzero(ptr, size);
	return (T_TRUE);
}
