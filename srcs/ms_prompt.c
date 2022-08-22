#include "minishell.h"

static void	ms_add_to_prompt(t_ribool first, char **prompt)
{
	char	*add_to_prompt;
	char	*concat_prompt;

	add_to_prompt = "\0";
	while (add_to_prompt && !(*add_to_prompt))
	{
		if (first)
			add_to_prompt = readline(PROMPT);
		else
			add_to_prompt = readline("> ");
	}
	if (!add_to_prompt)
		ms_exit(0, 0);
	concat_prompt = ft_strjoin((*prompt), add_to_prompt);
	ft_free_char(&add_to_prompt);
	if (!concat_prompt)
	{
		ft_free_char(&add_to_prompt);
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	}
	if (!first)
		ft_free_char(prompt);
	ft_free_char(prompt);
	*prompt = concat_prompt;
}

static void	ms_prompt_quotes(char **prompt, int *i)
{
	char	quote;
	char	*close_cote;

	quote = (*prompt)[(*i)++];
	while (quote && (*prompt)[*i])
	{
		if ((*prompt)[(*i)] == quote)
			quote = 0;
		(*i)++;
	}
	if (quote)
	{
		if (quote == '\'')
			close_cote = ft_strjoin(*prompt, "'");
		else
			close_cote = ft_strjoin(*prompt, "\"");
		if (!close_cote)
			ms_error(ERR_MEM, 0, 0, T_TRUE);
		ft_free_char(prompt);
		*prompt = close_cote;
		(*i)++;
	}
}

static t_ribool	ms_prompt_pipe(char **prompt, int *i)
{
	(*i)++;
	if ((*prompt)[(*i)] == '|')
		return (T_FALSE);
	while ((*prompt)[*i] == ' ')
		(*i)++;
	if (!(*prompt)[*i])
		ms_add_to_prompt(T_FALSE, prompt);
	while ((*prompt)[*i] == ' ')
		(*i)++;
	if ((*prompt)[(*i)] == '|')
		return (T_FALSE);
	return (T_TRUE);
}

static t_ribool	ms_prompt_redir(char **prompt, int *i)
{
	char		redir;

	redir = (*prompt)[(*i)++];
	if ((*prompt)[*i] == redir)
		(*i)++;
	while ((*prompt)[*i] == ' ')
		(*i)++;
	if (!((*prompt)[*i])
		|| ((*prompt)[*i] != redir && is_redir((*prompt)[*i])))
		return (T_FALSE);
	return (T_TRUE);
}

t_ribool	ms_prompt(char **prompt)
{
	int	i;

	ft_malloc_char(1, prompt);
	ms_add_to_prompt(T_TRUE, prompt);
	if (**prompt == '|')
		return (ft_free_char(prompt));
	i = 0;
	while ((*prompt)[i])
	{
		if ((*prompt)[i] == '\'' || (*prompt)[i] == '"')
			ms_prompt_quotes(prompt, &i);
		else if (is_redir((*prompt)[i]))
		{
			if (!ms_prompt_redir(prompt, &i))
				return (T_FALSE);
		}
		else if ((*prompt)[i] == '|')
		{
			if (!ms_prompt_pipe(prompt, &i))
				return (T_FALSE);
		}
		else
			i++;
	}
	return (T_TRUE);
}
