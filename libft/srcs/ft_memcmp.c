#include "./libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const void	*p1;
	const void	*p2;
	size_t		oct;

	p1 = s1;
	p2 = s2;
	oct = 0;
	while (oct < n)
	{
		if ((((unsigned char *)p1)[oct] - ((unsigned char *)p2)[oct]) != 0)
			return ((((unsigned char *)p1)[oct] - ((unsigned char *)p2)[oct]));
		oct++;
	}
	return (0);
}
