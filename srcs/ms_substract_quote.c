#include "minishell.h"

void	ms_copy_without_quote(char *split, char *tmp)
{
	int		src;
	int		dst;
	char	quote;

	src = -1;
	dst = 0;
	quote = 0;
	while (split[++src])
	{
		if (quote && split[src] == quote)
			quote = 0;
		else if (!quote && (split[src] == '\'' || split[src] == '"'))
			quote = split[src];
		else
			tmp[dst++] = split[src];
	}
}

t_ribool	ms_malloc_without_quote(char *split, char **tmp)
{
	int		src;
	int		len;
	char	quote;

	src = -1;
	len = 1;
	quote = 0;
	while (split[++src])
	{
		if (quote && split[src] == quote)
			quote = 0;
		else if (!quote && (split[src] == '\'' || split[src] == '"'))
			quote = split[src];
		else
			len++;
	}
	if (!(ft_malloc_char(len + 1, tmp)))
		return (T_FALSE);
	return (T_TRUE);
}

t_ribool	ms_subtract_quote_split(char **split)
{
	char	*tmp;

	tmp = NULL;
	while (*split)
	{
		if (!(ms_malloc_without_quote(*split, &tmp)))
			return (T_FALSE);
		ms_copy_without_quote(*split, tmp);
		ft_free_char(split);
		*(split++) = tmp;
	}
	return (T_TRUE);
}

t_ribool	ms_subtract_quote_cmd(char **cmd)
{
	char	*tmp;

	if (!(ms_malloc_without_quote(*cmd, &tmp)))
		return (T_FALSE);
	ms_copy_without_quote(*cmd, tmp);
	ft_free_char(cmd);
	*cmd = tmp;
	return (T_TRUE);
}
