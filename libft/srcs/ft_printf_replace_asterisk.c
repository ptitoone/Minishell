#include "./libft.h"

static void	ft_split_two(char **conv, char **split, va_list *alist)
{
	char	*arg;
	char	*tmp1;
	int		i;
	int		cv;

	i = 0;
	cv = va_arg(*alist, int);
	arg = ft_itoa(cv);
	tmp1 = ft_strjoin(split[i++], arg);
	free(arg);
	*conv = ft_strjoin(tmp1, split[i]);
	free(tmp1);
}

static void	ft_split_three(char **conv, char **split, va_list *alist)
{
	char	*arg;
	char	*tmp1;
	char	*tmp2;
	int		i;
	int		cv;

	i = 0;
	cv = va_arg(*alist, int);
	arg = ft_itoa(cv);
	tmp1 = ft_strjoin(split[i++], arg);
	free(arg);
	cv = va_arg(*alist, int);
	arg = ft_itoa(cv);
	tmp2 = ft_strjoin(split[i++], arg);
	free(arg);
	arg = ft_strjoin(tmp1, tmp2);
	*conv = ft_strjoin(arg, split[i]);
	free(arg);
	free(tmp1);
	free(tmp2);
}

void	ft_replace_asterisk(char **conv, va_list *alist)
{
	char	**split;
	int		len;
	int		x;

	split = ft_split(*conv, '*');
	len = 0;
	x = 0;
	free(*conv);
	while (split[len])
		len++;
	if (len == 3)
		ft_split_three(conv, split, alist);
	if (len == 2)
		ft_split_two(conv, split, alist);
	while (split[x])
		free(split[x++]);
	free(split[x]);
	free(split);
}
