#include "./libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	octet;

	octet = 0;
	while (octet < n)
		((unsigned char *)s)[octet++] = 0;
}
