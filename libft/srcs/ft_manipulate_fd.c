#include "./libft.h"

t_ribool	ft_close_fd(int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = -2;
	return (T_FALSE);
}

t_ribool	ft_unlink_file(char *file)
{
	if (file && !(access(file, F_OK)))
		unlink(file);
	return (T_FALSE);
}
