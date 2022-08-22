#include "./libft.h"

int	ft_isprint(int c)
{
	if ((c >= ' ' && c <= '\'') || (c >= '(' && c <= '/')
		|| (c >= '0' && c <= '?') || (c >= '@' && c <= '_')
		|| (c >= '`' && c <= '~'))
		return (1);
	return (0);
}
