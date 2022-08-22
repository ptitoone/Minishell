#include "minishell.h"

void	ms_envp_btree_add_elem(t_var_env *root, t_var_env *elem_add)
{
	while ((ft_strcmp(root->key, elem_add->key) > 0 && root->left)
		|| (ft_strcmp(root->key, elem_add->key) < 0 && root->right))
	{
		if (ft_strcmp(root->key, elem_add->key) > 0 && root->left)
			root = root->left;
		else if (ft_strcmp(root->key, elem_add->key) < 0 && root->right)
			root = root->right;
	}
	if (ft_strcmp(root->key, elem_add->key) > 0)
		root->left = elem_add;
	else if (ft_strcmp(root->key, elem_add->key) < 0)
		root->right = elem_add;
}

void	ms_envp_btree(t_var_env *head)
{
	t_var_env	*browse;

	head->left = NULL;
	head->right = NULL;
	browse = head->next;
	while (browse != head)
	{
		browse->left = NULL;
		browse->right = NULL;
		ms_envp_btree_add_elem(head, browse);
		browse = browse->next;
	}
}
