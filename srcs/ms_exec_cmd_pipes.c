#include "minishell.h"

t_ribool	ms_check_valid_token_param(t_token	*token, int *pfd, int *ret)
{
	if (!(ms_exec_open_files(token)))
	{
		if (pfd)
		{
			close(pfd[0]);
			pfd[0] = 0;
		}
		*ret = 1;
		return (T_FALSE);
	}
	if ((!(token->cmd_path) || stat(token->cmd_path, &(struct stat){}))
		&& !is_builtin(token->cmd_path))
	{
		if (pfd)
		{
			close(pfd[0]);
			pfd[0] = 0;
		}
		*ret = 127;
		return (T_FALSE);
	}
	*ret = 0;
	return (T_TRUE);
}

static void	exec_pipe_fork(t_ms_vars *ms_vars, t_token *token, int *pfd)
{
	signal(SIGQUIT, SIG_DFL);
	echo_control_seq(1);
	if (!ms_check_valid_token_param(ms_vars->token, 0, &pfd[3]))
		check_cmd(ms_vars, pfd[3]);
	if (token->infd)
		dup2(token->infd, 0);
	else
		dup2(pfd[2], 0);
	if (token->outfd > 1)
		dup2(token->outfd, 1);
	else if (token->next != NULL)
		dup2(pfd[1], 1);
	close(pfd[0]);
	if (*(ms_vars->token->cmd_path) == '/'
		|| !ft_strncmp(ms_vars->token->cmd_path, "./", 2)
		|| !ft_strncmp(ms_vars->token->cmd_path, "../", 3))
		execve(token->cmd_path, token->args, ms_vars->envp);
	else
		(exit(exec_builtin(ms_vars, token)));
	ms_error(strerror(errno), 0, 0, T_TRUE);
}

void	ms_exec_pipe_tail(int *pfd, t_token **token)
{
	close(pfd[1]);
	if (pfd[2] > 0)
		close(pfd[2]);
	pfd[2] = pfd[0];
	*token = (*token)->next;
}

static void	ms_init_pipe(int *pfd, pid_t *pid,
	t_token **head, t_ms_vars *ms_vars)
{
	pfd[2] = 0;
	*pid = 0;
	(*head) = ms_vars->token;
	ms_vars->in_fork = T_TRUE;
}

int	ms_exec_pipe(t_ms_vars *ms_vars)
{
	pid_t	pid;
	int		pfd[4];
	t_token	*head;

	ms_init_pipe(pfd, &pid, &head, ms_vars);
	while (ms_vars->token)
	{
		pipe(pfd);
		signal(SIGQUIT, &ms_signal);
		pid = fork();
		if (pid == -1)
			ms_error(strerror(errno), 0, 0, T_TRUE);
		else if (!pid)
			exec_pipe_fork(ms_vars, ms_vars->token, pfd);
		ms_exec_pipe_tail(pfd, &ms_vars->token);
	}
	waitpid(pid, &pfd[3], 0);
	signal(SIGQUIT, SIG_IGN);
	while (wait(0) != -1)
		;
	ms_vars->token = head;
	return (pfd[3]);
}
