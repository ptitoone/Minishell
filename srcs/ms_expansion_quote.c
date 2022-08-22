#include "minishell.h"

void	ms_expend_copy_single_quote(char **enter, char **expanded)
{
	*((*expanded)++) = *((*enter)++);
	while (*(*enter) && *(*enter) != '\'')
		*((*expanded)++) = *((*enter)++);
	if (*(*enter) && *(*enter) == '\'')
		*((*expanded)++) = *((*enter)++);
}

void	ms_expend_mllc_single_quote(char **enter, int *len)
{
	(*enter)++;
	while (*(*enter) && *(*enter) != '\'' && ++len)
		(*enter)++;
	if (*(*enter) && *(*enter) == '\'')
		(*enter)++;
}
