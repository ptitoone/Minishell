#include "libft.h"

void	ft_free_anon_array(void **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(array[i]);
		i++;
	}
}
