#include "./libft.h"

double	ft_atof(const char *str)
{
	int		strind;
	double	posinega;
	double	result;

	strind = 0;
	posinega = 1;
	while (str[strind] == ' ' || (str[strind] >= 9 && str[strind] <= 13))
		strind++;
	if (str[strind] == '-')
		posinega = -1;
	if (!(str[strind] == '-') && !(str[strind] == '+'))
		strind--;
	result = 0;
	while (str[++strind] >= '0' && str[strind] <= '9')
		result = (result * 10) + ((str[strind] - '0') * posinega);
	if (str[strind] != '.')
		return (result);
	while (str[++strind] >= '0' && str[strind] <= '9')
	{
		posinega *= 10.0;
		result += ((str[strind] - '0') / posinega);
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int		strind;
	int		posinega;
	int		result;

	strind = 0;
	posinega = 1;
	while (str[strind] == ' ' || (str[strind] >= 9 && str[strind] <= 13))
		strind++;
	if (str[strind] == '-')
		posinega = -1;
	if (!(str[strind] == '-') && !(str[strind] == '+'))
		strind--;
	result = 0;
	while (str[++strind] >= '0' && str[strind] <= '9')
		result = (result * 10) + ((str[strind] - '0') * posinega);
	return (result);
}

long int	ft_atol(const char *str)
{
	int			strind;
	int			posinega;
	long int	result;

	strind = 0;
	posinega = 1;
	while (str[strind] == ' ' || (str[strind] >= 9 && str[strind] <= 13))
		strind++;
	if (str[strind] == '-')
		posinega = -1;
	if (!(str[strind] == '-') && !(str[strind] == '+'))
		strind--;
	result = 0;
	while (str[++strind] >= '0' && str[strind] <= '9')
		result = (result * 10) + ((str[strind] - '0') * posinega);
	return (result);
}
