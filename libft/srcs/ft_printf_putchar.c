#include "./libft.h"

void	ft_putchar_pf(char c, int fd, t_conv *cv)
{
	char	ch;

	ch = c;
	if (write(fd, &ch, 1))
		cv->count++;
}
