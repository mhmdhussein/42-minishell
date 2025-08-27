/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:13:16 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/25 16:13:16 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reach_last_node(t_token **new_curr)
{
	while (*new_curr)
	{
		if ((*new_curr)->type == ENV_VAR)
			(*new_curr)->type = WORD;
		if (!(*new_curr)->next)
			break ;
		(*new_curr) = (*new_curr)->next;
	}
}

void	revert_word(t_token **tokens)
{
	t_token	*curr;

	if (!tokens || !(*tokens))
		return ;
	curr = *tokens;
	while (curr)
	{
		if (curr->type != WORD)
			curr->type = WORD;
		curr = curr->next;
	}
}

void	split_token(t_token **prev, t_token **curr, t_token **tokens)
{
	t_token	*new_list;
	t_token	*new_curr;

	if ((*curr)->value[0] == '\"' || (*curr)->value[0] == '\'')
		return ;
	new_list = split_tokenize((*curr)->value);
	if (!new_list)
		return ;
	revert_word(&new_list);
	if ((*prev))
		(*prev)->next = new_list;
	else
		*tokens = new_list;
	new_curr = new_list;
	reach_last_node(&new_curr);
	new_curr->next = (*curr)->next;
	free((*curr)->value);
	free((*curr));
	if ((*prev))
		(*curr) = (*prev)->next;
	else
		(*curr) = *tokens;
}
