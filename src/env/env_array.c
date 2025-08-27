/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:30:01 by mohhusse          #+#    #+#             */
/*   Updated: 2025/01/25 16:14:29 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env(t_env *env)
{
	int		count;
	t_env	*curr;

	count = 0;
	curr = env;
	while (curr)
	{
		if (curr->equal)
			count++;
		curr = curr->next;
	}
	return (count);
}

static char	*create_env_entry(t_env *env)
{
	char	*entry;
	char	*temp;

	if (!env->key || !env->value)
		return (NULL);
	temp = ft_strjoin(env->key, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, env->value);
	free(temp);
	return (entry);
}

char	**env_to_array(t_env *env)
{
	char	**env_array;
	int		env_count;
	int		i;

	env_count = count_env(env);
	env_array = (char **)malloc((env_count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->equal)
		{
			env_array[i] = create_env_entry(env);
			if (!env_array[i])
			{
				free_double_array(env_array);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
