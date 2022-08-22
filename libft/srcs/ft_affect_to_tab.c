#include "libft.h"

void	ft_affect_to_tab_2(void ***array, ...)
{
	va_list	alist;

	va_start(alist, array);
	while (**array)
	{
		**array = va_arg(alist, char *);
		(**array)++;
	}
	va_end(alist);
}
