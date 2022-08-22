#include "./libft.h"

int	ft_pad_space(int len, t_conv *cv)
{
	while (len-- > 0)
		if (write(1, " ", 1))
			cv->count++;
	return (len);
}
