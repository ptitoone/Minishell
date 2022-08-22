#include "minishell.h"

t_token	*ms_token_init(t_token **new_token)
{
	*new_token = (t_token *)malloc(sizeof(t_token));
	if (!(*new_token))
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	(*new_token)->cmd = 0;
	(*new_token)->args = 0;
	(*new_token)->cmd_path = 0;
	(*new_token)->infile = NULL;
	(*new_token)->outfile = NULL;
	(*new_token)->infd = 0;
	(*new_token)->outfd = 1;
	(*new_token)->append = T_FALSE;
	(*new_token)->hd = T_FALSE;
	(*new_token)->next = 0;
	return (*new_token);
}

void	ms_paths_init(t_ms_vars *ms_vars)
{
	t_var_env	*srch;

	ft_free_char_2_post(&(ms_vars->paths), 0);
	if (ms_env_elem_finder(ms_vars->head, "PATH", &srch))
	{
		ms_vars->paths = ft_split(srch->value, ':');
		if (!(ms_vars->paths))
			ms_error(ERR_MEM, 0, 0, T_TRUE);
	}
}

void	ms_envp_init(char **envp, t_ms_vars *ms_vars)
{
	int		elem;
	int		src;

	elem = -1;
	while (envp[++elem])
	{
		src = 0;
		ms_env_parse(envp[elem], ms_vars, &src);
	}
}

void	ms_init_cmd_kv(t_ms_vars *ms_vars)
{
	ms_vars->builtin[0].cmd = "echo";
	ms_vars->builtin[1].cmd = "cd";
	ms_vars->builtin[2].cmd = "pwd";
	ms_vars->builtin[3].cmd = "export";
	ms_vars->builtin[4].cmd = "unset";
	ms_vars->builtin[5].cmd = "env";
	ms_vars->builtin[6].cmd = "exit";
	ms_vars->builtin[7].cmd = NULL;
	ms_vars->builtin[0].fctn = ms_echo;
	ms_vars->builtin[1].fctn = ms_cd;
	ms_vars->builtin[2].fctn = ms_pwd_print;
	ms_vars->builtin[3].fctn = ms_export;
	ms_vars->builtin[4].fctn = ms_unset;
	ms_vars->builtin[5].fctn = ms_env_print;
	ms_vars->builtin[6].fctn = ms_exit;
	ms_vars->builtin[7].fctn = NULL;
}

void	ms_init(char **envp, t_ms_vars *ms_vars)
{
	char	buffer[301];

	ms_ctrl_c_interupt((void *)ms_vars);
	ms_vars->head = NULL;
	ms_vars->envp = NULL;
	ms_vars->paths = NULL;
	ms_vars->split = NULL;
	ms_vars->token = NULL;
	ms_vars->prompt = NULL;
	ms_vars->dup_stdin = 0;
	ms_vars->in_heredoc = T_FALSE;
	ms_vars->in_fork = T_FALSE;
	ms_init_cmd_kv(ms_vars);
	ms_exit(ms_vars, 0);
	ms_signal(0);
	getcwd(buffer, 300);
	if (!envp || !(*envp))
	{
		ms_env_elem_create(ft_strdup("?"), ft_strdup("0"), ms_vars);
		ms_env_elem_create(ft_strdup("PWD"), ft_strdup(buffer), ms_vars);
		ms_env_elem_create(ft_strdup("SHLVL"), ft_strdup("1"), ms_vars);
		ms_env_elem_create(ft_strdup("_"), ft_strdup("/usr/bin/env"), ms_vars);
	}
	else
		ms_envp_init(envp, ms_vars);
}
