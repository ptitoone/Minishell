#include "./libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	octet;

	octet = 0;
	if ((!dst && !src) && n)
		return (NULL);
	while (octet < n)
	{
		((unsigned char *)dst)[octet] = ((unsigned char *)src)[octet];
		octet++;
	}
	return (dst);
}
