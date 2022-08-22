#include "./libft.h"

void	ft_ltoa_init(long n, long *clclen, int *strlen, int *posinega)
{
	*clclen = n;
	*posinega = 1;
	*strlen = 2;
	if (n < 0)
		*posinega = -1;
	if (n < 0)
		*strlen = 3;
}

char	*ft_ltoa(long n)
{
	char	*nbrstr;
	long	clclen;
	int		strlen;
	int		posinega;

	ft_ltoa_init(n, &clclen, &strlen, &posinega);
	clclen /= 10;
	while (clclen)
	{
		clclen /= 10;
		strlen++;
	}
	nbrstr = (char *)malloc(strlen * sizeof(char));
	if (!nbrstr)
		return (0);
	nbrstr[--strlen] = '\0';
	while ((posinega < 0 && --strlen > 0) || (posinega > 0 && --strlen > -1))
	{
		nbrstr[strlen] = (((n % 10) * posinega) + '0');
		n /= 10;
	}
	nbrstr[0] = nbrstr[0];
	if (posinega < 0)
		nbrstr[0] = '-';
	return (nbrstr);
}

void	ft_itoa_init(int n, int *clclen, int *strlen, int *posinega)
{
	*clclen = n;
	*posinega = 1;
	*strlen = 2;
	if (n < 0)
		*posinega = -1;
	if (n < 0)
		*strlen = 3;
}

char	*ft_itoa(int n)
{
	char	*nbrstr;
	int		clclen;
	int		strlen;
	int		posinega;

	ft_itoa_init(n, &clclen, &strlen, &posinega);
	clclen /= 10;
	while (clclen)
	{
		clclen /= 10;
		strlen++;
	}
	nbrstr = (char *)malloc(strlen * sizeof(char));
	if (!nbrstr)
		return (0);
	nbrstr[--strlen] = '\0';
	while ((posinega < 0 && --strlen > 0) || (posinega > 0 && --strlen > -1))
	{
		nbrstr[strlen] = (((n % 10) * posinega) + '0');
		n /= 10;
	}
	nbrstr[0] = nbrstr[0];
	if (posinega < 0)
		nbrstr[0] = '-';
	return (nbrstr);
}
