/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:26:51 by mohhusse          #+#    #+#             */
/*   Updated: 2025/01/11 18:21:53 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env *env, t_shell *shell)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->equal == true)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	shell->last_exit_status = 0;
}
