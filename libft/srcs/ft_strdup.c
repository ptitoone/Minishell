#include "./libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned long int	len;
	char				*strdup;

	len = ft_strlen(s1);
	if (!ft_malloc_char((len + 1), &strdup))
		return (0);
	strdup[len] = '\0';
	while (len--)
		(strdup[len] = s1[len]);
	return (strdup);
}
