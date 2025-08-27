/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:46:03 by mohhusse          #+#    #+#             */
/*   Updated: 2025/06/14 18:46:03 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipes(t_token *tokens)
{
	t_token	*curr;
	int		has_pipe;

	if (tokens->type == PIPE)
		return (-1);
	curr = tokens;
	has_pipe = 0;
	while (curr)
	{
		if (curr->type == PIPE && curr->next == NULL)
			return (-1);
		else if (curr->type == PIPE && curr->next->type == PIPE)
			return (-1);
		if (curr->type == PIPE && has_pipe != 1)
			has_pipe = 1;
		curr = curr->next;
	}
	return (has_pipe);
}

void	decrement_shlvl(t_shell *shell)
{
	char	*shlvl;
	char	*level;
	int		lvl;

	shlvl = envget(shell->env, "SHLVL");
	if (!shlvl)
		lvl = 0;
	else
	{
		lvl = ft_atoi(shlvl) - 1;
		if (lvl < 0)
			lvl = 0;
	}
	level = ft_itoa(lvl);
	envset(shell->env, "SHLVL", level);
	free(level);
}

void	increment_shlvl(t_shell *shell)
{
	char	*shlvl;
	int		lvl;
	char	*lvl_str;

	shlvl = envget(shell->env, "SHLVL");
	if (!shlvl)
		lvl = 1;
	else
	{
		lvl = ft_atoi(shlvl) + 1;
		if (lvl < 0)
			lvl = 0;
	}
	lvl_str = ft_itoa(lvl);
	envset(shell->env, "SHLVL", lvl_str);
	free(lvl_str);
}
