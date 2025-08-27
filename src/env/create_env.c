/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:43:24 by mohhusse          #+#    #+#             */
/*   Updated: 2025/06/12 22:43:24 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_value(t_env **new_node, char *value)
{
	(*new_node)->value = ft_strdup(value);
	(*new_node)->equal = true;
	if (!(*new_node)->value)
	{
		free((*new_node)->key);
		free(*new_node);
	}
}

t_env	*create_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (value)
	{
		fill_value(&new_node, value);
		if (!new_node->value)
			return (NULL);
	}
	else
	{
		new_node->value = ft_strdup("");
		new_node->equal = false;
	}
	new_node->next = NULL;
	return (new_node);
}
