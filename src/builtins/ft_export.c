/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:32:06 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/22 14:46:47 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_copy(t_env *curr)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(curr->key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (curr->equal == true)
	{
		if (curr->value)
			new_node->value = ft_strdup(curr->value);
		else
			new_node->value = ft_strdup("");
		new_node->equal = true;
	}
	else
	{
		new_node->value = NULL;
		new_node->equal = false;
	}
	return (new_node);
}

t_env	*copy_env(t_env *env)
{
	t_env	*new_list;
	t_env	*new_node;
	t_env	*curr;

	new_list = NULL;
	curr = env;
	while (curr)
	{
		new_node = create_env_copy(curr);
		if (!new_node)
			return (NULL);
		new_node->next = new_list;
		new_list = new_node;
		curr = curr->next;
	}
	return (new_list);
}

void	print_export(t_env *env)
{
	t_env	*xenv;
	t_env	*curr;

	xenv = copy_env(env);
	xenv = merge_sort(xenv);
	curr = xenv;
	while (curr)
	{
		if (ft_strcmp(curr->key, "_"))
		{
			printf("declare -x %s", curr->key);
			if (curr->equal == true)
				printf("=\"%s\"", curr->value);
			printf("\n");
		}
		curr = curr->next;
	}
	free_env(xenv);
}

void	ft_export(t_cmd *cmd, t_shell *shell)
{
	int		i;

	shell->last_exit_status = 0;
	if (!cmd->args[1])
	{
		print_export(shell->env);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		export_arg(cmd->args[i], shell);
		i++;
	}
}
