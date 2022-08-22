#include "./libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	octet;

	octet = 0;
	while (octet < len)
	{
		((unsigned char *)b)[octet] = c;
		octet++;
	}
	return (b);
}
