#include "./libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		posinega;

	posinega = 1;
	if (n < 0)
		posinega = -1;
	if (n / 10)
		ft_putnbr_fd(n / 10, fd);
	else if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putchar_fd((((n % 10) * posinega) + '0'), fd);
}
