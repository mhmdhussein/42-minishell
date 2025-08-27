/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:24:10 by mohhusse          #+#    #+#             */
/*   Updated: 2025/03/29 13:24:10 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	revert_var(t_token	**tokens)
{
	t_token	*curr;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	while (curr && curr->next)
	{
		if (curr->type == HEREDOC && curr->next->type == ENV_VAR)
			curr->next->type = WORD;
		curr = curr->next;
	}
}

t_token_type	determine_token_type(char *value)
{
	if (ft_strcmp(value, "|") == 0)
		return (PIPE);
	if (ft_strcmp(value, "<") == 0)
		return (IN);
	if (ft_strcmp(value, ">") == 0)
		return (OUT);
	if (ft_strcmp(value, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (HEREDOC);
	if (ft_strchr(value, '$'))
		return (ENV_VAR);
	return (WORD);
}

int	counttokens(t_token *tokens)
{
	int		i;
	t_token	*curr;

	curr = tokens;
	i = 0;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

char	**detokenize(t_token *tokens)
{
	t_token	*curr;
	int		i;
	char	**args;

	curr = tokens;
	args = (char **)malloc(sizeof(char *) * (counttokens(tokens) + 1));
	i = 0;
	while (curr)
	{
		args[i] = ft_strdup(curr->value);
		curr = curr->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	remove_null(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (!curr->value)
		{
			if (prev)
				prev->next = curr->next;
			else
				*tokens = curr->next;
			free(curr);
			if (prev)
				curr = prev->next;
			else
				curr = *tokens;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
