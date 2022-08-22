#include "minishell.h"

static char	*ms_cd_get_path(t_ms_vars *ms_vars, char **args)
{
	t_var_env	*find;
	char		*path;

	find = NULL;
	path = NULL;
	if (!(args) || !(*args))
	{
		find = ms_env_elem_finder(ms_vars->head, "HOME", &find);
		if (find)
			path = ft_strdup(find->value);
		else
			path = ft_strdup("/");
	}
	else
		path = ft_strtrim((*args), " ");
	return (path);
}

int	ms_cd(t_ms_vars *ms_vars, char **args)
{
	char		*path;
	int			ret;
	t_var_env	*find;

	path = ms_cd_get_path(ms_vars, args);
	if (!path)
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	ret = chdir(path);
	if (!ret)
	{
		ms_env_elem_finder(ms_vars->head, "PWD", &find);
		ms_env_elem_create(ft_strdup("OLDPWD"), ft_strdup(find->value),
			ms_vars);
		ms_env_elem_create(ft_strdup("PWD"), getcwd(NULL, 0), ms_vars);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ms_error(path, " ", strerror(errno), T_FALSE);
		ret = 1;
	}
	free(path);
	return (ret);
}
