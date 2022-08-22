#include "./libft.h"

t_ribool	ft_free_char_2_post(char ***ptr, int delet)
{
	if (!(*ptr))
		return (T_FALSE);
	while ((*ptr)[delet])
		ft_free_char(&((*ptr)[delet++]));
	free(*ptr);
	*ptr = 0;
	return (T_FALSE);
}

t_ribool	ft_free_int_2_post(int ***ptr, int delet)
{
	if (!(*ptr))
		return (T_FALSE);
	while ((*ptr)[delet])
		ft_free_int(&((*ptr)[delet++]));
	free(*ptr);
	*ptr = 0;
	return (T_FALSE);
}

t_ribool	ft_free_float_2_post(float ***ptr, int delet)
{
	if (!(*ptr))
		return (T_FALSE);
	while ((*ptr)[delet])
		ft_free_float(&((*ptr)[delet++]));
	free(*ptr);
	*ptr = 0;
	return (T_FALSE);
}

t_ribool	ft_free_double_2_post(double ***ptr, int delet)
{
	if (!(*ptr))
		return (T_FALSE);
	while ((*ptr)[delet])
		ft_free_double(&((*ptr)[delet++]));
	free(*ptr);
	*ptr = 0;
	return (T_FALSE);
}

t_ribool	ft_free_t_ribool_2_post(t_ribool ***ptr, int delet)
{
	if (!(*ptr))
		return (T_FALSE);
	while ((*ptr)[delet])
		ft_free_t_ribool(&((*ptr)[delet++]));
	free(*ptr);
	*ptr = 0;
	return (T_FALSE);
}
