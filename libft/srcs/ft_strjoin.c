#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	strlen;
	size_t	strlen2;

	if (!s1 || !s2)
		return (0);
	strlen = ft_strlen(s1);
	strlen2 = ft_strlen(s2);
	strlen += strlen2;
	str = (char *)malloc((strlen + 1) * sizeof(char));
	if (!str)
		return (0);
	str[strlen] = '\0';
	while (strlen2)
		str[--strlen] = ((char *)s2)[--strlen2];
	while (strlen--)
		str[strlen] = ((char *)s1)[strlen];
	return (str);
}

t_ribool	ft_strjoin_all_malloc(int ac, char **av, char c, char **str)
{
	int		str_len;
	int		ind_av;

	str_len = 0;
	if (ac > 1 && c)
		str_len = (ac - 1);
	ind_av = -1;
	while (++ind_av < ac)
	{
		if (av[ind_av])
			str_len += ft_strlen(av[ind_av]);
		else if (ac > 1 && c)
			str_len -= 1;
	}
	if (!ft_malloc_char(str_len + 1, str))
		return (T_FALSE);
	return (T_TRUE);
}

void	ft_strjoin_all_copy(int ac, char **av, char c, char *str)
{
	int		ind_str;
	int		ind_av;

	ind_av = -1;
	ind_str = 0;
	while (++ind_av < ac)
	{
		if (av[ind_av])
			ind_str += ft_strlcpy(str + ind_str, av[ind_av],
					(ft_strlen(av[ind_av]) + 1));
		if (av[ind_av] && av[ind_av + 1] && c)
			str[ind_str++] = c;
	}
	str[ind_str] = '\0';
}

t_ribool	ft_strjoin_all(int ac, char **av, char c, char **str)
{
	if (!(ft_strjoin_all_malloc(ac, av, c, str)))
		return (T_FALSE);
	ft_strjoin_all_copy(ac, av, c, *str);
	return (T_TRUE);
}
