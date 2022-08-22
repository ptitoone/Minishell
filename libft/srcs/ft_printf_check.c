#include "./libft.h"

int	ft_check(const char c)
{
	if (c == '-' || c == '.' || c == '*' || (c >= '0' && c <= '9'))
		return (1);
	if (ft_is_spec(c))
		return (1);
	return (0);
}
