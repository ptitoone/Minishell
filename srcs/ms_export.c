#include "minishell.h"

void	ms_export_envp_var(t_var_env *new_elem)
{
	char	*joined;

	joined = 0;
	ft_free_char(&(new_elem->env));
	if (new_elem->value)
	{
		joined = ft_strjoin(new_elem->key, "=");
		if (!joined)
			ms_error(ERR_MEM, 0, 0, T_TRUE);
		new_elem->env = ft_strjoin(joined, new_elem->value);
	}
	else
		new_elem->env = ft_strdup(new_elem->key);
	ft_free_char(&joined);
	if (!(new_elem->env))
		ms_error(ERR_MEM, 0, 0, T_TRUE);
}

void	ms_export_envp_table(t_ms_vars *ms_vars)
{
	t_var_env	*browse;
	int			envp_len;

	envp_len = 0;
	if (ms_vars->envp)
		ft_free_char_2_pre(&(ms_vars->envp), 0);
	browse = ms_vars->head;
	while (browse->next != ms_vars->head)
	{
		ms_export_envp_var(browse);
		envp_len++;
		browse = browse->next;
	}
	ms_export_envp_var(browse);
	envp_len++;
	if (!(ft_malloc_char_2(envp_len + 1, &(ms_vars->envp))))
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	(ms_vars->envp)[envp_len] = NULL;
	while (envp_len--)
	{
		(ms_vars->envp)[envp_len] = browse->env;
		browse = browse->prev;
	}
}

t_ribool	ms_export_key_check(char *src)
{
	int	i;

	i = 0;
	if (src && !(ft_isalnum(src[0])))
		return (T_FALSE);
	while (src[i] && src[i] != '=')
	{
		if (!ft_isalnum(src[i]) && src[i] != '_')
			return (T_FALSE);
		i++;
	}
	return (T_TRUE);
}

int	ms_export(t_ms_vars *ms_vars, char **args)
{
	int		ret;
	int		src;

	ret = 0;
	if (args && *args)
	{
		while (args && *args)
		{
			if (!ms_export_key_check(*args))
				ret = ms_error("`", *args, ERR_IDENT, T_FALSE) + 1;
			else
			{
				src = 0;
				ms_env_parse(*args, ms_vars, &src);
				ms_export_envp_table(ms_vars);
				ms_envp_btree(ms_vars->head);
			}
			args++;
		}
		ms_paths_init(ms_vars);
	}
	else
		ms_export_infix(ms_vars->head);
	return (ret);
}
