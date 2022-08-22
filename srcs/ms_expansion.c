#include "minishell.h"

static void	ms_expand_value_len(char **src, int *len, t_var_env *env)
{
	t_var_env	*browse;

	browse = env;
	browse->prev->next = 0;
	(*src)++;
	while (browse && (ft_strncmp(*src, browse->key, ft_strlen(browse->key))
			|| (ft_isalnum((*src)[ft_strlen(browse->key)])
			|| (*src)[ft_strlen(browse->key)] == '_')))
		browse = browse->next;
	env->prev->next = env;
	while (**src && (ft_isalnum(**src) || **src == '_' || **src == '?'))
		(*src)++;
	if (browse)
		(*len) += ft_strlen(browse->value);
}

t_ribool	ms_expand_mllc(char *i, char **expanded,
	t_var_env *env, t_ribool here_doc)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (*i)
	{
		if (!quote && *i == '"')
			quote = *i;
		else if (quote == *i)
			quote = 0;
		if (!here_doc && !quote && *i == '\'' && ++len)
			ms_expend_mllc_single_quote(&i, &len);
		else if ((*i) == '$' && (*(i + 1)) && (*(i + 1)) != ' ')
			ms_expand_value_len(&i, &len, env);
		else if (++i)
			len++;
	}
	if (!(ft_malloc_char(len + 1, expanded)))
		return (T_FALSE);
	return (T_TRUE);
}

static void	ms_expand_copy_value(char *i, char **expand, t_var_env *env)
{
	int			src;
	t_var_env	*browse;

	browse = env;
	browse->prev->next = 0;
	while (browse && (ft_strncmp(i, browse->key, ft_strlen(browse->key))
			|| (ft_isalnum(i[ft_strlen(browse->key)])
				|| i[ft_strlen(browse->key)] == '_')))
		browse = browse->next;
	env->prev->next = env;
	src = 0;
	while (browse && (browse->value)[src])
		*((*expand)++) = (browse->value)[src++];
}

void	ms_expand_copy(char *i, char *expanded,
	t_var_env *env, t_ribool here_doc)
{
	char	quote;

	quote = 0;
	while (*i)
	{
		if (!quote && *i == '"')
			quote = *i;
		else if (*i == '"')
			quote = 0;
		if (!here_doc && !quote && (*i) == '\'')
			ms_expend_copy_single_quote(&i, &expanded);
		else if ((*i) == '$' && (*(i + 1)) && (*(i + 1)) != ' ')
		{
			ms_expand_copy_value(++i, &expanded, env);
			while (*i && (ft_isalnum(*i) || *i == '_' || *i == '?'))
				i++;
		}
		else
			*(expanded++) = *(i++);
	}
	*expanded = '\0';
}

void	ms_expand(t_ms_vars *ms_vars, t_var_env *env)
{
	char	*expanded;
	int		i;

	expanded = NULL;
	i = -1;
	while ((ms_vars->split)[++i])
	{
		if (!(ft_strncmp((ms_vars->split)[i], "<<", 2)))
			expanded = ft_strdup((ms_vars->split)[i]);
		else if (ms_expand_mllc((ms_vars->split)[i], &expanded,
			env, T_FALSE))
			ms_expand_copy((ms_vars->split)[i], expanded, env, T_FALSE);
		if (!expanded)
		{
			ft_free_char_2_post(&(ms_vars->split), 0);
			ms_error(ERR_MEM, 0, 0, T_TRUE);
		}
		ft_free_char(&((ms_vars->split)[i]));
		(ms_vars->split)[i] = ft_strdup(expanded);
		ft_free_char(&expanded);
	}
}
