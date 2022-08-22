#include "minishell.h"

t_ribool	ms_exec_open_files(t_token *token)
{
	if (token->infile)
		token->infd = open(token->infile, O_RDONLY);
	if (token->infd == -1)
	{
		token->infd = 0;
		return (ms_error(token->infile, ": ", strerror(errno), T_FALSE));
	}
	if (token->outfile && token->append)
		token->outfd = open(token->outfile, O_WRONLY | O_APPEND);
	else if (token->outfile)
		token->outfd = open(token->outfile, O_WRONLY | O_TRUNC);
	if (token->outfd == -1)
	{
		token->outfd = 1;
		return (ms_error(token->outfile, ": ", strerror(errno), T_FALSE));
	}
	return (T_TRUE);
}

int	exec_builtin(t_ms_vars *ms_vars, t_token *token)
{
	int		i;
	int		ret;

	i = 0;
	ms_vars->in_fork = T_FALSE;
	while (ft_strcmp(token->cmd_path, ms_vars->builtin[i].cmd))
		i++;
	ret = (((ms_vars->builtin)[i]).fctn)(ms_vars,
			token->args + 1);
	return (ret * 256);
}

static int	exec_fork(t_ms_vars *ms_vars)
{
	pid_t	pid;
	int		stat_loc;

	errno = 0;
	ms_vars->in_fork = T_TRUE;
	stat_loc = 0;
	signal(SIGQUIT, &ms_signal);
	pid = fork();
	if (pid == -1)
		ms_error(strerror(errno), 0, 0, T_TRUE);
	if (!pid)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		echo_control_seq(1);
		dup2(ms_vars->token->infd, 0);
		dup2(ms_vars->token->outfd, 1);
		execve(ms_vars->token->cmd_path, ms_vars->token->args, ms_vars->envp);
		ms_error(strerror(errno), 0, 0, T_TRUE);
	}
	wait(&stat_loc);
	signal(SIGQUIT, SIG_IGN);
	ms_vars->in_fork = T_FALSE;
	return (stat_loc);
}

static void	ms_exec_cmd_tail(int *ret, t_ms_vars *ms_vars)
{
	if (WIFSIGNALED(*ret))
		*ret = WTERMSIG(*ret) + 128;
	else if (WIFEXITED(*ret))
		*ret = WEXITSTATUS(*ret);
	ms_vars->in_fork = T_FALSE;
	ms_env_elem_create(ft_strdup("?"), ft_itoa(*ret), ms_vars);
	ms_export_envp_table(ms_vars);
	ms_envp_btree(ms_vars->head);
}

void	ms_exec_cmd(t_ms_vars *ms_v)
{
	int			ret;
	t_var_env	*f;

	ms_env_elem_finder(ms_v->head, "PATH", &f);
	if (ms_v->token)
	{
		if (ms_v->token->next)
			ret = ms_exec_pipe(ms_v);
		else if (ms_check_valid_token_param(ms_v->token, 0, &ret))
		{
			if (is_builtin(ms_v->token->cmd_path))
				ret = exec_builtin(ms_v, ms_v->token);
			else
				ret = exec_fork(ms_v);
		}
		else if (ret == 127 && !ms_v->token->hd
			&& (!f || (f && f->value && !*f->value)))
			ms_error(*(ms_v->token->args), ": No such file or directory",
				0, T_FALSE);
		else if (ret == 127 && !ms_v->token->hd)
			ms_error(*(ms_v->token->args), ": command not found",
				0, T_FALSE);
		ms_exec_cmd_tail(&ret, ms_v);
	}
}
