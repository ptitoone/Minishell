#include "./libft.h"

size_t	ft_nb_w(char *str, char chr)
{
	size_t	index;
	size_t	nb_w;

	index = 0;
	nb_w = 0;
	while (str[index])
	{
		while (str[index] && str[index] == chr)
			index++;
		if (str[index])
			nb_w++;
		while (str[index] && str[index] != chr)
			index++;
	}
	return (nb_w);
}

char	*ft_add_word(char **str, char chr)
{
	size_t	wrdlen;
	char	*word;
	size_t	index;

	wrdlen = 0;
	while (str[0][wrdlen] && str[0][wrdlen] != chr)
		wrdlen++;
	word = (char *)malloc((wrdlen + 1) * sizeof(char));
	if (!word)
		return (0);
	index = 0;
	while (str[0][0] && str[0][0] != chr)
	{
		word[index] = str[0][0];
		index++;
		(str[0])++;
	}
	word[index] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tw;
	size_t	nb_w;
	size_t	cw;
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	nb_w = ft_nb_w(str, c);
	if (!ft_malloc_char_2(nb_w + 1, &tw))
		return (0);
	cw = -1;
	while (++cw < nb_w)
	{
		while (str[0] && str[0] == c)
			str++;
		tw[cw] = ft_add_word(&str, c);
		if (!(tw[cw]))
			return ((char **)ft_free_char_2_pre(&tw, cw));
	}
	tw[nb_w] = 0;
	return (tw);
}
