#include "minishell.h"

static void	ms_token_cmd_end(char *crnt, int *end)
{
	char	quote;

	quote = 0;
	*end = 0;
	while (crnt[(*end)] && (quote || crnt[(*end)] != '|'))
	{
		if ((crnt[(*end)] == '\'' || crnt[(*end)] == '"') && !quote)
			quote = crnt[(*end)];
		else if (quote && crnt[(*end)] == quote)
			quote = 0;
		(*end)++;
	}
	while (crnt[(*end) - 1] == ' ')
		(*end)--;
}

static void	ms_token_cmd_mllc(char *crnt, t_token *token, int end)
{
	char	quote;
	int		src;
	int		mlc;
	int		chevron;

	quote = 0;
	src = -1;
	mlc = 0;
	while (++src < end)
	{
		chevron = 1;
		if (!quote && src - 1 > -1 && is_redir(crnt[src - 1]))
			chevron = 0;
		if (quote && crnt[src] == quote)
			quote = 0;
		else if (!quote && (crnt[src] == '\'' || crnt[src] == '"'))
			quote = crnt[src];
		if (!quote && crnt[src] == ' ')
			while (crnt[src + chevron] == ' ')
				src++;
		mlc++;
	}
	if (!(ft_malloc_char((mlc + 1), &(token->cmd))))
		ms_error("no memory found", 0, 0, T_TRUE);
}

static void	ms_token_cmd_copy(char **crnt, char *dst, int end)
{
	char	quote;
	int		src;
	int		cpy;
	int		chevron;

	quote = 0;
	src = -1;
	cpy = 0;
	while (++src < end)
	{
		chevron = 1;
		if (!quote && src - 1 > -1 && is_redir((*crnt)[src - 1]))
			chevron = 0;
		if (quote && (*crnt)[src] == quote)
			quote = 0;
		else if (!quote && ((*crnt)[src] == '\'' || (*crnt)[src] == '"'))
			quote = (*crnt)[src];
		else if (!quote && (*crnt)[src] == ' ')
			while ((*crnt)[src + chevron] == ' ')
				src++;
		dst[cpy++] = (*crnt)[src];
	}
	(*crnt) += src;
	while (**crnt && (**crnt) == ' ')
		(*crnt)++;
}

static void	ms_token_split(char *prompt, t_token **token)
{
	char	*crnt;
	int		end;
	t_token	*new_token;

	crnt = prompt;
	new_token = NULL;
	while (*crnt)
	{
		while ((*crnt) && ft_isspace(*crnt))
			crnt++;
		if (*crnt)
		{
			if (!(*token))
				(*token) = ms_token_init(&(new_token));
			else
				new_token = ms_token_init(&((new_token)->next));
			ms_token_cmd_end(crnt, &end);
			ms_token_cmd_mllc(crnt, new_token, end);
			ms_token_cmd_copy(&crnt, new_token->cmd, end);
			if (*crnt == '|')
				(crnt)++;
		}
	}
}

void	ms_lexer(t_ms_vars *ms_vars)
{
	int	i;

	while (1)
	{
		i = 2;
		echo_control_seq(0);
		if (ms_vars->token)
			ms_free_tokens(ms_vars->token);
		ms_vars->token = NULL;
		if (ms_prompt(&(ms_vars->prompt)))
		{
			ms_token_split(ms_vars->prompt, &(ms_vars->token));
			if (ms_token_format(ms_vars))
				ms_exec_cmd(ms_vars);
			while (++i <= 256)
				close(i);
			errno = 0;
		}
		else if (!(ms_error("invalid syntax", 0, 0, T_FALSE)))
			ms_env_elem_create(ft_strdup("?"), ft_strdup("258"), ms_vars);
		add_history(ms_vars->prompt);
		ft_free_char(&(ms_vars->prompt));
	}
}
