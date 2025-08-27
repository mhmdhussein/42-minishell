/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:53:19 by mohhusse          #+#    #+#             */
/*   Updated: 2025/01/25 14:26:02 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*merge_split(t_env *env)
{
	t_env	*fast;
	t_env	*slow;
	t_env	*temp;

	fast = env;
	slow = env;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		if (fast)
			slow = slow->next;
	}
	temp = slow->next;
	slow->next = NULL;
	return (temp);
}

t_env	*merge(t_env *first, t_env *second)
{
	if (!first)
		return (second);
	if (!second)
		return (first);
	if (ft_strcmp(first->key, second->key) < 0)
	{
		first->next = merge(first->next, second);
		return (first);
	}
	else
	{
		second->next = merge(first, second->next);
		return (second);
	}
}

t_env	*merge_sort(t_env *env)
{
	t_env	*second;

	if (env == NULL || env->next == NULL)
		return (env);
	second = merge_split(env);
	env = merge_sort(env);
	second = merge_sort(second);
	return (merge(env, second));
}
