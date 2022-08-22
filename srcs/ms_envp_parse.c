#include "minishell.h"

void	ms_env_key_gen(char *varp, char *key, int *src_varp)
{
	int			dest;
	char		quote;

	dest = 0;
	quote = 0;
	while (varp[(*src_varp)] && varp[(*src_varp)] != '='
		&& varp[(*src_varp)] != ' ')
	{
		if ((varp[(*src_varp)] == '\'' || varp[(*src_varp)] == '\"') && !quote)
			quote = varp[(*src_varp)];
		else if (varp[(*src_varp)] == quote)
			quote = 0;
		else
			key[dest++] = varp[(*src_varp)];
		(*src_varp)++;
	}
}

void	ms_env_key_len(char *varp, char **key, char *quote, int *src_varp)
{
	int		len;
	int		src;

	len = 0;
	src = *src_varp;
	while (varp[src] && varp[src] != '=' && varp[src] != ' ' && len != -1)
	{
		if ((varp[src] == '\'' || varp[src] == '\"') && !(*quote))
			(*quote) = varp[src];
		else if (varp[src] == (*quote))
			(*quote) = 0;
		else
			len++;
		src++;
	}
	if (!(ft_malloc_char(len + 1, key)))
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	else
		ms_env_key_gen(varp, *key, src_varp);
}

void	ms_env_value_gen(char *varp, char *value, char *quote, int *src_varp)
{
	int			dest;

	dest = 0;
	while (varp[(*src_varp)] && ((varp[(*src_varp)] == ' ' && (*quote))
			|| varp[(*src_varp)] != ' '))
	{
		if ((varp[(*src_varp)] == '\'' || varp[(*src_varp)] == '\"')
			&& !(*quote))
			(*quote) = varp[(*src_varp)];
		else if (varp[(*src_varp)] == (*quote))
			(*quote) = 0;
		else
			value[dest++] = varp[(*src_varp)];
		(*src_varp)++;
	}
}

void	ms_env_parse(char *varp, t_ms_vars *ms_vars, int *src_varp)
{
	char	*key;
	char	*value;
	char	quote;

	key = 0;
	quote = 0;
	ms_env_key_len(varp, &key, &quote, src_varp);
	value = 0;
	if (varp[*src_varp] == '=')
	{
		value = key;
		(*src_varp)++;
		value = ft_strdup((varp + (*src_varp)));
		if (!value)
			ms_error(ERR_MEM, 0, 0, T_TRUE);
	}
	ms_env_elem_create(key, value, ms_vars);
}
