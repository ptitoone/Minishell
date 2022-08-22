#include "minishell.h"

t_ribool	ms_strtrim(char *arg, char **to_unset, char **args)
{
	int	src;
	int	dst;

	src = -1;
	dst = 0;
	while (arg[++src] && arg[src])
	{
		if (!ft_isalnum(arg[src]) && arg[src] != '_')
			return (T_FALSE);
		dst++;
	}
	if (!(ft_malloc_char(src + 1, to_unset)))
	{
		ft_free_char_2_pre(&args, 0);
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	}
	src = -1;
	dst = -1;
	while (arg[++src])
		if (ft_isalnum(arg[src]) || arg[src] == '_')
			(*to_unset)[++dst] = arg[src];
	return (T_TRUE);
}

int	ms_unset(t_ms_vars *ms_vars, char **args)
{
	char		*arg;
	int			src;
	int			ret;

	if (!args)
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	src = -1;
	arg = NULL;
	ret = 0;
	while (args && args[++src])
	{
		if (!(ms_strtrim(args[src], &arg, args)))
			ret = ms_error("`", args[src], ERR_IDENT, T_FALSE) + 1;
		else
		{
			ms_env_elem_delet(ms_vars, arg);
			ms_envp_btree(ms_vars->head);
			ms_export_envp_table(ms_vars);
			ft_free_char(&arg);
		}
	}
	ms_paths_init(ms_vars);
	return (ret);
}
