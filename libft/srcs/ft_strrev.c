#include "./libft.h"

void	ft_strrev(char *str)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) - 1;
	if (str)
	{
		while (i < j)
		{
			tmp = str[i];
			str[i++] = str[j];
			str[j--] = tmp;
		}
	}
}
