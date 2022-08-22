#include "./libft.h"

int	ft_has_flag(const char *conv)
{
	while (*conv)
	{
		if (*conv == '-' && *(conv - 1) != '.')
			return ('-');
		if (*conv == '0' && *(conv + 1) != '-' && *(conv - 1) != '.'
			&& !((*(conv - 1) >= '1' && *(conv - 1) <= '9')))
			return ('0');
		conv++;
	}
	return (0);
}
