#include "./libft.h"

t_ribool	ft_long_overflow(const char *src)
{
	long	num;
	char	*ltoa;
	int		ret_val;
	char	*val_trim;

	num = ft_atol(src);
	ltoa = ft_ltoa(num);
	val_trim = ft_strtrim(src, " ");
	ret_val = ft_strcmp(val_trim, ltoa);
	free(ltoa);
	free(val_trim);
	if (!ret_val)
		return (T_FALSE);
	return (T_TRUE);
}
