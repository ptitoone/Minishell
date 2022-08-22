#include "./libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*sour;
	unsigned char	*dest;

	sour = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (dest > sour)
		while (len--)
			*(dest + len) = *(sour + len);
	else if (dest < sour)
		while (len--)
			*dest++ = *sour++;
	return (dst);
}
