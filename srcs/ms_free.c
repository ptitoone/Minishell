#include "minishell.h"

void	ms_free_token(t_token *token)
{
	ft_free_char(&(token->cmd));
	ft_free_char(&(token->cmd_path));
	ft_free_char_2_post(&token->args, 0);
	ft_free_char(&(token->infile));
	ft_close_fd(&(token->infd));
	ft_free_char(&(token->outfile));
	ft_close_fd(&(token->outfd));
	free(token);
	token = NULL;
}

void	ms_free_tokens(t_token *tokens)
{
	t_token	*to_free_token;

	while (tokens)
	{
		to_free_token = tokens;
		tokens = tokens->next;
		ms_free_token(to_free_token);
	}
}
