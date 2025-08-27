/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:23:07 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/26 14:27:44 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	call_remove_quotes(t_token **curr)
{
	char	*temp;

	temp = (*curr)->value;
	(*curr)->value = remove_quotes((*curr)->value);
	free(temp);
}

char	*protect_backslash(char *value)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (value);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\\')
			result = appendchar(result, '\\');
		result = appendchar(result, value[i]);
		i++;
	}
	free(value);
	return (result);
}

void	expand_variables(t_token **tokens, t_shell *shell)
{
	t_token	*curr;
	t_token	*prev;
	char	*expanded;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		curr->value = protect_backslash(curr->value);
		if (curr->type == ENV_VAR)
		{
			expanded = expand_token(curr->value, shell);
			free(curr->value);
			curr->value = expanded;
			curr->type = WORD;
			if ((!prev || prev->type != HEREDOC) && curr->value)
				split_token(&prev, &curr, tokens);
		}
		if ((!prev || prev->type != HEREDOC) && curr->value)
			call_remove_quotes(&curr);
		prev = curr;
		curr = curr->next;
	}
}
