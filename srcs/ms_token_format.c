#include "minishell.h"

static void	ms_parse_cmd_build_args(char **split, char ***args)
{
	int		i;
	int		count;
	char	**browse;

	i = -1;
	count = 0;
	while (split[++i])
		if (!(is_redir(*split[i])))
			count++;
	if (!ft_malloc_char_2(count + 1, args))
	{
		free(split);
		ms_error("no memory found", 0, 0, T_TRUE);
	}
	browse = (*args);
	i = -1;
	while (split[++i])
	{
		if (!(is_redir(*split[i])))
			*(browse++) = split[i];
		else
			ft_free_char(&split[i]);
	}
}

static void	ms_split_cmd_delimiter(char **cmd)
{
	char	quote;

	quote = 0;
	if (**cmd && is_redir(**cmd))
		(*cmd)++;
	if (**cmd && is_redir(**cmd))
		(*cmd)++;
	while (**cmd && (!(!quote && ((**cmd) == ' ' || is_redir(**cmd)))))
	{
		if ((**cmd == '\'' || **cmd == '"') && !quote)
			quote = **cmd;
		else if ((**cmd == '\'' || **cmd == '"') && **cmd == quote)
			quote = 0;
		(*cmd)++;
	}
}

static t_ribool	ms_split_cmd(char ***args, char *cmd, int recur)
{
	char	*arg;

	arg = cmd;
	ms_split_cmd_delimiter(&cmd);
	if (is_redir(*cmd))
	{
		if (!(ms_split_cmd(args, cmd, recur + 1)))
			return (ft_free_char_2_post(args, recur));
	}
	else if (*cmd && !(ms_split_cmd(args, cmd + 1, recur + 1)))
		return (ft_free_char_2_post(args, recur + 1));
	else if (!(*cmd) && !(ft_malloc_char_2(recur + 2, args)))
		return (T_FALSE);
	*cmd = '\0';
	(*args)[recur] = ft_strdup(arg);
	if (!((*args)[recur]))
		return (ft_free_char(&((*args)[recur])));
	return (T_TRUE);
}

t_ribool	ms_token_format(t_ms_vars *ms_vars)
{
	t_token	*browse;
	int		id;

	browse = ms_vars->token;
	id = 0;
	while (browse)
	{
		if (!(ms_split_cmd(&(ms_vars->split), browse->cmd, 0)))
			ms_error("no memory found", 0, 0, T_TRUE);
		ms_expand(ms_vars, ms_vars->head);
		ms_subtract_quote_split(ms_vars->split);
		if (!ms_vars->split)
			ms_error("no memory found.", 0, 0, T_TRUE);
		if (!(ms_parse_io_file(browse, id++, ms_vars)))
			return (ft_free_char_2_post(&(ms_vars->split), 0));
		ms_parse_cmd_build_args(ms_vars->split, &(browse->args));
		ft_free_char_2_pre(&(ms_vars->split), 0);
		browse->cmd_path = ms_find_cmd(*(browse->args), ms_vars->paths);
		ft_free_char_2_post(&(ms_vars->split), 0);
		browse = browse->next;
	}
	return (T_TRUE);
}
