#include "minishell.h"

char	*ms_find_bin(char *cmd, char **paths)
{
	struct stat	buff;
	int			i;
	char		*join;

	i = -1;
	if (*cmd && !ft_isalnum(*cmd))
	{
		join = ft_strdup(cmd);
		if (!join)
			ms_error(ERR_MEM, 0, 0, T_TRUE);
		return (join);
	}
	while (*cmd && ft_isalnum(*cmd) && paths && paths[++i])
	{
		ft_strjoin_all(3, (char *[]){paths[i], "/", cmd}, 0, &join);
		if (!join)
			ms_error(ERR_MEM, 0, 0, T_TRUE);
		if (!stat(join, &buff))
			return (join);
		ft_free_char(&join);
	}
	return (NULL);
}

char	*ms_find_cmd(char *cmd, char **paths)
{
	char		*join;
	int			i;

	i = -1;
	join = NULL;
	if (is_builtin(cmd))
		return (ft_strdup(cmd));
	if (cmd && !stat(cmd, &(struct stat){}))
	{
		if (*cmd == '/' || !ft_strncmp(cmd, "./", 2)
			|| !ft_strncmp(cmd, "../", 3))
			return (ft_strdup(cmd));
		else if (ft_isalpha(*cmd) && (!paths || !(*paths)))
			return (ft_strjoin("./", cmd));
	}
	if (cmd && paths)
	{
		join = ms_find_bin(cmd, paths);
		return (join);
		if (!stat(cmd, &(struct stat){}) && is_not_in_cdir(cmd))
			return (ft_strjoin("./", cmd));
	}
	return (NULL);
}

t_ribool	ms_error(char *error1, char *error2, char *error3, t_ribool exit)
{
	ft_putstr_fd("minishell: ", 2);
	if (error1)
		ft_putstr_fd(error1, 2);
	if (error2)
		ft_putstr_fd(error2, 2);
	if (error3)
		ft_putstr_fd(error3, 2);
	ft_putchar_fd('\n', 2);
	if (exit)
		ms_exit(0, 0);
	return (T_FALSE);
}

int	main(int ac, char **av, char **envp)
{
	t_ms_vars	ms_vars;

	if (ac != 1 && av[1])
		ms_error(ERR_ARG, 0, 0, T_TRUE);
	ms_init(envp, &ms_vars);
	ms_export_envp_table(&ms_vars);
	ms_envp_btree(ms_vars.head);
	ms_paths_init(&ms_vars);
	ms_lexer(&ms_vars);
	return (0);
}
