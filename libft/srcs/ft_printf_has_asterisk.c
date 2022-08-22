#include "./libft.h"

int	ft_has_asterisk(const char *s)
{
	if (!s)
		return (0);
	while (*s != 0)
	{
		if (*s == '*')
			return (1);
		s++;
	}
	return (0);
}
