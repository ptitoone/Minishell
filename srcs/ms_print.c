#include "minishell.h"

void	ms_export_print(t_var_env *root)
{
	if (*root->key != '?')
	{
		ft_printf("declare -x %s", root->key);
		if (root->value)
			ft_printf("=\"%s\"", root->value);
		ft_printf("\n");
	}
}

void	ms_export_infix(t_var_env *root)
{
	if (root)
	{
		if (root->left)
			ms_export_infix(root->left);
		ms_export_print(root);
		if (root->right)
			ms_export_infix(root->right);
	}
}

int	ms_pwd_print(t_ms_vars *ms_vars, char **args)
{
	char		buff[1024];

	if (ms_vars && !args)
		;
	getcwd(buff, 1024);
	ft_putstr_fd(buff, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int	ms_env_print(t_ms_vars *ms_vars, char **args)
{
	t_var_env	*browse;

	if (*args)
		return (1);
	browse = ms_vars->head;
	while (browse && browse != ms_vars->head->prev)
	{
		if (*browse->env != '?' && browse->value)
		{
			ft_putstr_fd(browse->env, 1);
			ft_putchar_fd('\n', 1);
		}
		browse = browse->next;
	}
	if (browse && *browse->env != '?' && browse->value)
	{
		ft_putstr_fd(browse->env, 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
