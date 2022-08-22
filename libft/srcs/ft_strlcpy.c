#include "./libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	srclen;

	if (!dst || !src)
		return (0);
	srclen = ft_strlen(src);
	index = -1;
	if (dstsize)
		while (src[++index] && index < dstsize - 1)
			dst[index] = src[index];
	dst[index] = '\0';
	return (srclen);
}
