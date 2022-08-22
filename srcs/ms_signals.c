#include "minishell.h"

void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}

t_ribool	ms_check_exit(int *ret_val, char **exit_code)
{
	*ret_val = (ft_atoi(exit_code[0]));
	if (*ret_val < 0 || *ret_val > 255)
		*ret_val = *ret_val % 256;
	if (ft_long_overflow(exit_code[0]))
	{
		*ret_val = 255;
		ft_putstr_fd("minishell-4.2: exit: ", 2);
		ft_putstr_fd(exit_code[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (exit_code[1] && exit_code[1][0])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (T_FALSE);
	}		
	return (T_TRUE);
}

int	ms_exit(t_ms_vars *ms_vars, char **args)
{
	static t_ms_vars	*exit_v;
	int					ret_val;
	int					fd;

	if (!exit_v)
		exit_v = ms_vars;
	else
	{
		ret_val = 0;
		ft_putstr_fd("exit\n", 1);
		fd = 3;
		while (fd < 256)
			close(fd++);
		if (!args || !(*args) || ms_check_exit(&ret_val, args))
		{
			while (exit_v->head)
				ms_env_elem_delet(exit_v, NULL);
			ft_free_char_2_pre(&(exit_v->envp), 0);
			if (!(ft_free_char_2_post(&(exit_v->paths), 0)) && exit_v->prompt)
				ft_free_char(&(exit_v->prompt));
			ms_free_tokens(exit_v->token);
			exit(ret_val);
		}
	}
	return (1);
}

void	ms_ctrl_c_interupt(void *init)
{
	static t_ms_vars	*ms_vars;

	if (!ms_vars)
		ms_vars = init;
	else if (!ms_vars->in_fork)
	{
		if (ms_vars->in_heredoc == 1)
		{
			write(1, "\n", 1);
			ms_env_elem_create(ft_strdup("?"), ft_strdup("1"), ms_vars);
			close(ms_vars->dup_stdin);
		}
		else
		{
			write(1, "\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else
		write(1, "\n", 2);
}

void	ms_signal(int sig)
{
	if (!sig)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ms_signal);
	}
	else if (sig == SIGINT)
		ms_ctrl_c_interupt(0);
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == SIGTERM)
		ms_exit(0, 0);
}
