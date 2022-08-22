#include "./libft.h"

int	ft_is_spec(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X')
	{
		return (1);
	}
	return (0);
}
