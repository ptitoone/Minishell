#include "./libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	octet;

	octet = -1;
	while (s[++octet] || (char)c == '\0')
		if (s[octet] == (char)c)
			return ((char *)s + octet);
	return (0);
}
