/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:30:32 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/20 13:43:41 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	addenv(t_env *env, char *key, char *value)
{
	t_env	*curr;

	if (!env)
	{
		env = create_env(key, value);
		return ;
	}
	curr = env;
	while (curr->next)
		curr = curr->next;
	curr->next = create_env(key, value);
}

char	*envget(t_env *env, char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key) && curr->equal == true)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

void	envset(t_env *env, char *key, char *value)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (curr->value)
				free(curr->value);
			curr->value = ft_strdup(value);
			curr->equal = true;
			return ;
		}
		curr = curr->next;
	}
	addenv(env, key, value);
}

void	addenv2(t_env **env, char *key, char *value)
{
	t_env	*curr;

	if (!env || !(*env))
	{
		*env = create_env(key, value);
		return ;
	}
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = create_env(key, value);
}
