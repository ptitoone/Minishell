#include "minishell.h"

static t_ribool	ms_free_close_here_doc(char **ppt, char **expanded,
						t_ms_vars *ms_vars, t_token *token)
{
	if (!(ms_expand_mllc(*ppt, expanded, ms_vars->head, T_TRUE)))
	{
		ft_free_char_2_post(&(ms_vars->split), 0);
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	}
	ms_expand_copy(*ppt, *expanded, ms_vars->head, T_TRUE);
	ft_putstr_fd(*expanded, token->infd);
	ft_putstr_fd("\n", token->infd);
	ft_free_char(ppt);
	ft_free_char(expanded);
	return (T_FALSE);
}

t_ribool	ms_write_here_doc(t_token *token, char *del, t_ms_vars *ms_vars)
{
	static char		*ppt;
	static char		*expanded;
	int				r;

	ms_vars->dup_stdin = dup(0);
	unlink(token->infile);
	token->infd = open(token->infile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (token->infd == -1)
		ms_error(strerror(errno), 0, 0, T_FALSE);
	ms_vars->in_heredoc = 1;
	errno = 0;
	r = get_next_line(ms_vars->dup_stdin, &ppt);
	while (r != -1 && ft_strcmp(del, ppt)
		&& !ms_free_close_here_doc(&ppt, &expanded, ms_vars, token))
		r = get_next_line(ms_vars->dup_stdin, &ppt);
	if (!ft_free_char(&expanded) && !ft_free_char(&ppt) && r == -1
		&& errno == ENOMEM && !(ft_free_char_2_post(&(ms_vars->split), 0)))
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	ms_vars->in_heredoc = 0;
	ft_close_fd(&(token->infd));
	if (fstat(ms_vars->dup_stdin, &(struct stat){}) == -1)
		return (T_FALSE);
	token->hd = T_TRUE;
	return (T_TRUE);
}

t_ribool	ms_infl(t_token *token, char *str,
				int nb_token, t_ms_vars *ms_vars)
{
	char	*args_doc[3];

	ft_free_char(&(token->infile));
	if (*str == '<')
	{
		if (!nb_token)
			token->infile = strdup("/tmp/.ms_here_doc.tmp");
		else
		{
			args_doc[0] = ft_strdup("/tmp/.ms_here_doc(");
			args_doc[1] = ft_itoa(nb_token);
			args_doc[2] = ft_strdup(").tmp");
			ft_strjoin_all(3, args_doc, 0, &(token->infile));
		}
	}
	else
		token->infile = strdup(str);
	if (!(token->infile))
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	else if (*str == '<' && !(ms_write_here_doc(token, str + 1, ms_vars)))
		return (T_FALSE);
	return (T_TRUE);
}

t_ribool	ms_parse_outfile_open(t_token *token)
{
	token->outfd = open(token->outfile, O_CREAT, 0644);
	ft_close_fd(&(token->outfd));
	token->outfd = 1;
	if (access(token->outfile, W_OK) == -1)
		return (T_FALSE);
	return (T_TRUE);
}

t_ribool	ms_parse_io_file(t_token *token, int id, t_ms_vars *ms_vars)
{
	char	**split;

	split = ms_vars->split;
	while (*split)
	{
		if (**split == '>')
		{
			if ((*split)[1] != '>')
				token->outfile = ft_strdup(*split + 1);
			else
			{
				token->outfile = ft_strdup(*split + 2);
				token->append = T_TRUE;
			}
			if (!(ms_parse_outfile_open(token)))
				break ;
		}
		else if (**split == '<' && !(ms_infl(token, (*split) + 1, id, ms_vars)))
			return (T_FALSE);
		else if (**split == '<' && *(*split + 1) != '<'
			&& access(token->infile, R_OK) == -1)
			break ;
		split++;
	}
	return (T_TRUE);
}
