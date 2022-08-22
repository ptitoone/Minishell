#include "./libft.h"

int	ft_issigned(int c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}
