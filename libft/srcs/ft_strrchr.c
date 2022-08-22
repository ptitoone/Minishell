#include "./libft.h"

char	*ft_strrchr(const char *s, int c)
{
	long int	octet;

	octet = ft_strlen(s);
	while (s[octet] != (char)c && octet > -1)
		octet--;
	if (s[octet] == (char)c && octet > -1)
		return ((char *)s + octet);
	return (0);
}
