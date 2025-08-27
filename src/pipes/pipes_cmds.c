/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:48:14 by mohhusse          #+#    #+#             */
/*   Updated: 2025/06/14 18:48:14 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_command(t_token **curr, int i)
{
	while (i)
	{
		if ((*curr)->type == PIPE)
			i--;
		(*curr) = (*curr)->next;
	}
}

t_token	*parse_tokens(t_token **tokens, int i)
{
	t_token			*curr;
	t_token			*new_token;
	t_token			*head;

	curr = *tokens;
	head = NULL;
	while (curr)
	{
		find_command(&curr, i);
		while (curr && curr->type != PIPE)
		{
			new_token = create_token(curr->value);
			if (!new_token)
				return (NULL);
			new_token->type = curr->type;
			add_token(&head, &new_token);
			curr = curr->next;
		}
		if (curr && curr->type == PIPE)
			break ;
		if (curr)
			curr = curr->next;
	}
	return (head);
}

t_token	*extract_tokens(t_token *tokens, int i)
{
	t_token	*head;

	if (!tokens)
		return (NULL);
	head = parse_tokens(&tokens, i);
	if (!head)
		return (NULL);
	revert_var(&head);
	return (head);
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_tokens = NULL;
	cmd->append = false;
	cmd->delim = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

void	parse_commands(t_token *tokens, t_shell *shell)
{
	t_token	*curr;
	t_cmd	*curr_cmd;
	t_cmd	*cmd;
	int		i;

	curr = tokens;
	i = 1;
	while (curr)
	{
		if (curr->type == PIPE)
			i++;
		curr = curr->next;
	}
	while (i--)
	{
		cmd = create_cmd();
		if (!cmd)
			return ;
		if (!shell->cmds)
			shell->cmds = cmd;
		else
			curr_cmd->next = cmd;
		curr_cmd = cmd;
	}
}
