#include "minishell.h"

t_var_env	*ms_env_elem_finder(t_var_env *root, char *search, t_var_env **elem)
{
	if (search)
	{
		while (root && ft_strcmp(root->key, search))
		{
			if (ft_strcmp(root->key, search) > 0)
				root = root->left;
			else if (ft_strcmp(root->key, search) < 0)
				root = root->right;
		}
	}
	if (elem)
		(*elem) = root;
	return (root);
}

void	ms_env_elem_remove(t_ms_vars *ms_vars, t_var_env *remove_elem)
{
	if (remove_elem)
	{
		if (ms_vars->head == ms_vars->head->next)
			ms_vars->head = 0;
		else
		{
			if (ms_vars->head == remove_elem)
				ms_vars->head = ms_vars->head->next;
			remove_elem->prev->next = remove_elem->next;
			remove_elem->next->prev = remove_elem->prev;
		}
	}
}

void	ms_env_elem_delet(t_ms_vars *ms_vars, char *delet)
{	
	t_var_env	*delet_elem;

	if (ms_env_elem_finder(ms_vars->head, delet, &delet_elem))
	{
		ms_env_elem_remove(ms_vars, delet_elem);
		if (delet && !ft_strcmp(delet, "PATH"))
			ft_free_char_2_post(&(ms_vars->paths), 0);
		ft_free_char(&(delet_elem->key));
		ft_free_char(&(delet_elem->value));
		ft_free_char(&(delet_elem->env));
		free(delet_elem);
	}
}

void	ms_env_elem_add(t_ms_vars *ms_vars, t_var_env *elem_add)
{
	t_var_env	*last;

	elem_add->prev = elem_add;
	elem_add->next = elem_add;
	if (!(ms_vars->head))
		ms_vars->head = elem_add;
	else
	{
		last = ms_vars->head->prev;
		elem_add->prev = last;
		elem_add->next = ms_vars->head;
		last->next = elem_add;
		ms_vars->head->prev = elem_add;
	}
}

void	ms_env_elem_create(char *key, char *value, t_ms_vars *ms_vars)
{
	t_var_env	*new_elem;

	if (!(ms_env_elem_finder(ms_vars->head, key, &(new_elem))))
	{
		new_elem = (t_var_env *)malloc(sizeof(t_var_env));
		new_elem->env = NULL;
		new_elem->key = NULL;
		new_elem->value = NULL;
		new_elem->prev = NULL;
		new_elem->next = NULL;
		new_elem->left = NULL;
		new_elem->right = NULL;
	}
	else
		ms_env_elem_remove(ms_vars, new_elem);
	if (!ft_free_char(&new_elem->key) && !new_elem)
	{
		ft_free_char(&key);
		ft_free_char(&value);
		ms_error(ERR_MEM, 0, 0, T_TRUE);
	}
	new_elem->key = key;
	if (value && !(ft_free_char(&new_elem->value)))
		new_elem->value = value;
	ms_env_elem_add(ms_vars, new_elem);
}
