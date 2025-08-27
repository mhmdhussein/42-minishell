/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:45:57 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/20 13:56:05 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_prompt(t_shell *shell, bool expand, int tmp_fd, char *delim)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		restoresignals_heredoc();
		heredoc_prompt(shell, expand, tmp_fd, delim);
		free_pipe_child(shell);
		exit(0);
	}
	else
	{
		ignoresignals();
		wait(&shell->last_exit_status);
		if (WIFSIGNALED(shell->last_exit_status)
			&& WTERMSIG(shell->last_exit_status) == SIGINT)
		{
			shell->last_exit_status = 130;
			shell->interrupt = true;
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	setupsignals();
}

void	process_heredoc(t_token *heredoc, t_cmd *cmd, t_shell *shell)
{
	char	*tmpfile;
	int		tmp_fd;
	bool	expand;
	int		pipe_fd;

	expand = true;
	tmpfile = create_tmp(shell);
	add_heredoc(tmpfile, shell);
	tmp_fd = open(tmpfile, O_WRONLY | O_CREAT, 0644);
	if (tmp_fd == -1)
		return ;
	cmd->delim = heredoc->next->value;
	if (ft_strchr(cmd->delim, '\"') || ft_strchr(cmd->delim, '\''))
		expand = false;
	cmd->delim = remove_quotes_heredoc(cmd->delim);
	dup2(shell->std_in, STDIN_FILENO);
	pipe_fd = dup(STDOUT_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	fork_prompt(shell, expand, tmp_fd, cmd->delim);
	close_heredoc(&cmd, tmpfile, pipe_fd, tmp_fd);
	heredoc_to_in(&heredoc, tmpfile);
}

void	remove_heredoc(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

	if (!tokens || !(*tokens))
		return ;
	curr = *tokens;
	prev = NULL;
	while (curr && curr->next)
	{
		if (curr->type == HEREDOC)
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

int	heredoc_count(t_token *tokens)
{
	t_token	*curr;
	int		count;

	curr = tokens;
	count = 0;
	while (curr)
	{
		if (curr->type == HEREDOC)
			count++;
		curr = curr->next;
	}
	return (count);
}

void	handle_heredoc(t_shell *shell, t_cmd *cmd, t_token **tokens)
{
	t_token	*curr;
	int		heredocs;

	curr = *tokens;
	heredocs = heredoc_count(*tokens);
	while (curr)
	{
		if (curr->type == HEREDOC && curr->next && curr->next->type == WORD)
		{
			if (heredocs != 1)
			{
				process_heredoc_special(curr, shell);
				remove_heredoc(tokens);
			}
			else
				process_heredoc(curr, cmd, shell);
			curr = *tokens;
			heredocs--;
		}
		else
			curr = curr->next;
	}
	if (cmd->input_fd != -1)
		close(cmd->input_fd);
}
