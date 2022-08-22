#include "./libft.h"

t_ribool	ft_error(const char *msg, const char *msg2)
{
	if (msg)
	{
		ft_putstr_fd("Error - ", 2);
		ft_putstr_fd(((char *)msg), 2);
	}
	if (msg2)
	{
		ft_putstr_fd(" :\n", 2);
		ft_putstr_fd((char *)msg2, 2);
	}
	if (msg)
		ft_putstr_fd(".\n", 2);
	return (T_FALSE);
}

t_ribool	ft_freerror(const char *msg, const char *msg2)
{
	ft_error(msg, msg2);
	free ((char *)msg2);
	return (T_FALSE);
}

t_ribool	ft_memerror(const char *forfree)
{
	free((char *)forfree);
	ft_putstr_fd("No memory place found", 2);
	return (T_FALSE);
}
