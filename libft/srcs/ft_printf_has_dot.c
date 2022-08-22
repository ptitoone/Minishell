#include "./libft.h"

int	ft_has_dot(const char *s)
{
	while (*(s++) != 0)
		if (*s == '.')
			return (1);
	return (0);
}
