/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:27:00 by mohhusse          #+#    #+#             */
/*   Updated: 2025/02/08 14:25:17 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*create_token(char *split)
{
	t_token		*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(split);
	if (!new_node->value)
		return (free(new_node), NULL);
	new_node->type = determine_token_type(split);
	new_node->next = NULL;
	return (new_node);
}

void	add_token(t_token **head, t_token **newnode)
{
	t_token	*curr;

	if (!(*head))
	{
		*head = *newnode;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = *newnode;
}

t_token	*create_token_list(char **split)
{
	t_token	*head;
	t_token	*new_node;
	int		i;

	i = 0;
	head = NULL;
	while (split[i])
	{
		new_node = create_token(split[i++]);
		if (new_node == NULL)
			return (free_tokens(head), NULL);
		add_token(&head, &new_node);
	}
	return (head);
}

t_token	*tokenize(char *input)
{
	char	**split;
	t_token	*token_list;

	split = split_input(input);
	if (!split)
		return (NULL);
	token_list = create_token_list(split);
	revert_var(&token_list);
	free_double_array(split);
	return (token_list);
}

t_token	*split_tokenize(char *input)
{
	char	**split;
	t_token	*token_list;

	split = ft_split_tokenize(input, ' ');
	if (!split)
		return (NULL);
	token_list = create_token_list(split);
	revert_var(&token_list);
	free_double_array(split);
	return (token_list);
}
