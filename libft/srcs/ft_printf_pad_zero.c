#include "./libft.h"

int	ft_pad_zero(int len, t_conv *cv)
{
	while (len-- > 0)
	{
		if (write(1, "0", 1))
			cv->count++;
	}
	return (len);
}
