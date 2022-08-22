#include "./libft.h"

void	ft_putstr_len(const char *s, size_t len, t_conv *cv)
{
	unsigned long	i;

	i = 0;
	if (s)
		while (i < len)
			if (write(1, &s[i++], 1))
				cv->count++;
}
