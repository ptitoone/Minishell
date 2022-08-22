#include "minishell.h"

void	check_cmd(t_ms_vars *ms_vars, int ret)
{
	t_var_env	*f;

	ms_env_elem_finder(ms_vars->head, "PATH", &f);
	if (ret == 127 && !ms_vars->token->hd
		&& (!f || (f && f->value && !*f->value)))
		ms_error(*(ms_vars->token->args), ": No such file or directory",
			0, T_FALSE);
	else if (ret == 127 && !ms_vars->token->hd)
		ms_error(*(ms_vars->token->args), ": command not found",
			0, T_FALSE);
}

t_ribool	is_builtin(char *cmd)
{
	if (cmd)
	{
		if (!ft_strcmp(cmd, "echo"))
			return (T_TRUE);
		if (!ft_strcmp(cmd, "cd"))
			return (T_TRUE);
		if (!ft_strcmp(cmd, "pwd"))
			return (T_TRUE);
		if (!ft_strcmp(cmd, "export"))
			return (T_TRUE);
		if (!ft_strcmp(cmd, "unset"))
			return (T_TRUE);
		if (!ft_strcmp(cmd, "env"))
			return (T_TRUE);
		if (!ft_strcmp(cmd, "exit"))
			return (T_TRUE);
	}
	return (T_FALSE);
}

t_ribool	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (T_TRUE);
	return (T_FALSE);
}

t_ribool	is_not_in_cdir(char *path)
{
	while (*path)
	{
		if (*path == '/')
			return (T_TRUE);
		path++;
	}
	return (T_FALSE);
}
