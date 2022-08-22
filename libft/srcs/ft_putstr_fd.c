#include "./libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned long int	strind;

	strind = 0;
	while (s && s[strind])
		ft_putchar_fd(s[strind++], fd);
}
