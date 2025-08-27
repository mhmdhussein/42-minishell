/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:30:19 by mohhusse          #+#    #+#             */
/*   Updated: 2025/05/14 14:14:58 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_in(t_token *in, t_cmd *cmd, t_shell *shell)
{
	if (cmd->input_fd != -1)
		close(cmd->input_fd);
	cmd->input_fd = open(in->next->value, O_RDONLY);
	if (cmd->input_fd == -1)
	{
		dup2(shell->std_out, STDOUT_FILENO);
		printf("-bash: %s: %s\n", in->next->value, strerror(errno));
		shell->last_exit_status = 1;
		cmd->input_fd = -2;
		return ;
	}
	dup2(cmd->input_fd, STDIN_FILENO);
}

void	process_out(t_token *out, t_cmd *cmd, t_shell *shell)
{
	if (cmd->output_fd != -1)
		close(cmd->output_fd);
	cmd->output_fd = open(out->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->output_fd == -1)
	{
		printf("-bash: %s: %s\n", out->next->value, strerror(errno));
		shell->last_exit_status = 1;
		cmd->input_fd = -2;
		return ;
	}
	dup2(cmd->output_fd, STDOUT_FILENO);
}

void	process_append(t_token *app, t_cmd *cmd, t_shell *shell)
{
	if (cmd->output_fd != -1)
		close(cmd->output_fd);
	cmd->output_fd = open(app->next->value,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->output_fd == -1)
	{
		printf("-bash: %s: %s\n", app->next->value, strerror(errno));
		shell->last_exit_status = 1;
		cmd->input_fd = -2;
		return ;
	}
	dup2(cmd->output_fd, 1);
}

void	remove_redirection(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

	if (!tokens || !(*tokens))
		return ;
	curr = *tokens;
	prev = NULL;
	while (curr && curr->next)
	{
		if (curr->type == IN || curr->type == OUT || curr->type == APPEND)
		{
			if (prev)
				prev->next = curr->next->next;
			else
				*tokens = curr->next->next;
			free(curr->next->value);
			free(curr->next);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	process_redirections(t_shell *shell, t_cmd *cmd, t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		if (cmd->input_fd == -2)
			break ;
		if (curr->type == IN)
			process_in(curr, cmd, shell);
		else if (curr->type == OUT)
			process_out(curr, cmd, shell);
		else if (curr->type == APPEND)
			process_append(curr, cmd, shell);
		if ((curr->type == IN || curr->type == OUT || curr->type == APPEND))
		{
			remove_redirection(tokens);
			curr = *tokens;
		}
		else
			curr = curr->next;
	}
	if (cmd->input_fd != -1)
		close(cmd->input_fd);
	if (cmd->output_fd != -1)
		close(cmd->output_fd);
}
