#include "minishell.h"

static void	echo_opt(char **args, t_ribool *opt, int *index)
{
	int	i;

	*opt = T_FALSE;
	*index = 0;
	while (args[*index] && args[*index][0])
	{
		i = 0;
		if (args[*index][i++] == '-' || args[*index][i++] == 'n')
			while (args[*index][i] == 'n')
				i++;
		if (args[*index][0] == '-' && args[*index][1] == 'n'
			&& !(args[*index][i]))
		{
			*opt = T_TRUE;
			(*index)++;
		}
		else
			break ;
	}
}

int	ms_echo(t_ms_vars *ms_vars, char **args)
{
	t_ribool	opt;
	int			i;

	echo_opt(args, &opt, &i);
	while (args && args[i])
	{
		ft_putstr_fd(args[i], ms_vars->token->outfd);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (!opt)
		write (ms_vars->token->outfd, "\n", 1);
	return (0);
}
