#include "./libft.h"

t_ribool	ft_malloc_char(int size, char **ptr)
{
	*ptr = (char *)malloc(size * sizeof(char));
	if (!(*ptr))
		return (T_FALSE);
	while (size--)
		(*ptr)[size] = 0;
	return (T_TRUE);
}

t_ribool	ft_malloc_int(int size, int **ptr)
{
	*ptr = (int *)malloc(size * sizeof(int));
	if (!(*ptr))
		return (T_FALSE);
	while (size--)
		(*ptr)[size] = 0;
	return (T_TRUE);
}

t_ribool	ft_malloc_float(int size, float **ptr)
{
	*ptr = (float *)malloc(size * sizeof(float));
	if (!(*ptr))
		return (T_FALSE);
	while (size--)
		(*ptr)[size] = 0;
	return (T_TRUE);
}

t_ribool	ft_malloc_double(int size, double **ptr)
{
	*ptr = (double *)malloc(size * sizeof(double));
	if (!(*ptr))
		return (T_FALSE);
	while (size--)
		(*ptr)[size] = 0;
	return (T_TRUE);
}

t_ribool	ft_malloc_t_ribool(int size, t_ribool **ptr)
{
	*ptr = (t_ribool *)malloc(size * sizeof(t_ribool));
	if (!(*ptr))
		return (T_FALSE);
	while (size--)
		(*ptr)[size] = 0;
	return (T_TRUE);
}
