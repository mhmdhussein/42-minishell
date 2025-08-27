/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:40:23 by mohhusse          #+#    #+#             */
/*   Updated: 2025/05/14 14:22:13 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*curr;
	t_cmd	*next;

	if (!cmds)
		return ;
	curr = cmds;
	while (curr)
	{
		next = curr->next;
		free_double_array(curr->args);
		free_tokens(curr->cmd_tokens);
		if (curr->delim)
			free(curr->delim);
		free(curr);
		curr = next;
	}
}

void	free_env(t_env *env)
{
	t_env	*curr;
	t_env	*next;

	if (!env)
		return ;
	curr = env;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;
	t_token	*curr;

	if (!tokens)
		return ;
	curr = tokens;
	while (curr)
	{
		temp = curr;
		curr = curr->next;
		free(temp->value);
		free(temp);
	}
}

void	free_double_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
