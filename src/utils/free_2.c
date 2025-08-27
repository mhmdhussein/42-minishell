/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 20:03:50 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/06 20:03:50 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipe_child(t_shell *shell)
{
	free_cmds(shell->cmds);
	shell->cmds = NULL;
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	free_heredocs(shell->heredocs);
	shell->heredocs = NULL;
	dup2(shell->std_out, STDOUT_FILENO);
	dup2(shell->std_in, STDIN_FILENO);
	if (shell->std_in != -1)
		close(shell->std_in);
	if (shell->std_out != -1)
		close(shell->std_out);
	free_env(shell->env);
	free(shell->current_pwd);
	free(shell->original_home);
}

void	free_heredocs(t_heredoc *heredocs)
{
	t_heredoc	*curr;
	t_heredoc	*next;

	curr = heredocs;
	next = NULL;
	while (curr)
	{
		next = curr->next;
		free(curr->filename);
		free(curr);
		curr = next;
	}
}

void	unlink_heredocs(t_heredoc *heredocs)
{
	t_heredoc	*curr;
	t_heredoc	*next;

	curr = heredocs;
	next = NULL;
	while (curr)
	{
		next = curr->next;
		unlink(curr->filename);
		free(curr->filename);
		free(curr);
		curr = next;
	}
}

void	free_dup_close(t_shell *shell)
{
	free_cmds(shell->cmds);
	shell->cmds = NULL;
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	unlink_heredocs(shell->heredocs);
	shell->heredocs = NULL;
	dup2(shell->std_out, STDOUT_FILENO);
	dup2(shell->std_in, STDIN_FILENO);
	if (shell->std_in != -1)
		close(shell->std_in);
	if (shell->std_out != -1)
		close(shell->std_out);
}
