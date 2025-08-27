/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:49:17 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/22 16:49:16 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_key(char *assign)
{
	int	i;

	if (!assign || !*assign)
		return (0);
	if (!is_var_char(assign[0], 1))
		return (0);
	i = 1;
	while (assign[i] && is_var_char(assign[i], 0))
		i++;
	if (assign[i])
		return (0);
	return (1);
}

int	update_existing(t_shell *shell, t_env *env)
{
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, env->key))
		{
			if (env->value)
			{
				free(curr->value);
				curr->value = env->value;
				if (curr->equal == false && curr->value[0] != '\0')
					curr->equal = true;
			}
			free(env->key);
			free(env);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	addtoenv(t_shell *shell, t_env *env)
{
	t_env	*curr;

	if (!shell->env)
		shell->env = env;
	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	curr->next = env;
}

void	export_env(t_shell *shell, char *key, char *value, char *temp)
{
	t_env	*new_env;

	new_env = create_env(key, value);
	if (!new_env)
		return ;
	if (ft_strchr(temp, '='))
		new_env->equal = true;
	else
		new_env->equal = false;
	if (!update_existing(shell, new_env))
		addtoenv(shell, new_env);
}

void	export_arg(char *assign, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*temp;

	temp = ft_strdup(assign);
	key = ft_strtok(assign, "=");
	value = ft_strtok(NULL, "");
	if (!valid_key(key) || temp[0] == '=')
	{
		printf("bash: export: '%s': not a valid identifier\n", temp);
		shell->last_exit_status = 1;
		free(temp);
		return ;
	}
	if (!ft_strcmp(key, "_"))
	{
		free(temp);
		return ;
	}
	export_env(shell, key, value, temp);
	free(temp);
}
