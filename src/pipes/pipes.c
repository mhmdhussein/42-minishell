/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:01:36 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/22 17:16:40 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes( t_cmd *cmd, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
}

void	execute_pipe_child(t_shell *shell, int prev_fd, t_cmd *cmd
		, int *pipe_fd)
{
	restoresignals();
	decrement_shlvl(shell);
	close_pipes(cmd, prev_fd, pipe_fd);
	if (!redirections(shell, cmd, &cmd->cmd_tokens))
	{
		free_pipe_child(shell);
		exit(shell->last_exit_status);
	}
	if (cmd->cmd_tokens)
	{
		cmd->args = detokenize(cmd->cmd_tokens);
		if (is_builtin(cmd->args[0]))
			exec_builtin(cmd, shell);
		else
			execute_command(cmd, shell);
	}
	free_pipe_child(shell);
	exit(shell->last_exit_status);
}

void	pipe_parent(int *prev_fd, t_cmd **cmd, int *pipe_fd)
{
	ignoresignals();
	if (*prev_fd != -1)
		close(*prev_fd);
	if ((*cmd)->next)
		close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
	(*cmd) = (*cmd)->next;
}

void	handle_pipes(t_shell *shell)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	pid_t	pid;
	int		prev_fd;
	int		status;

	cmd = shell->cmds;
	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0)
			execute_pipe_child(shell, prev_fd, cmd, pipe_fd);
		else
			pipe_parent(&prev_fd, &cmd, pipe_fd);
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		continue ;
	shell->last_exit_status = WEXITSTATUS(status);
	setupsignals();
}

void	exec_pipes(t_shell *shell)
{
	t_cmd	*cmd_curr;
	int		i;

	shell->pipe_mode = true;
	shell->std_out = dup(STDOUT_FILENO);
	if (!redirection_syntax(shell))
		return ;
	parse_commands(shell->tokens, shell);
	cmd_curr = shell->cmds;
	i = 0;
	while (cmd_curr)
	{
		cmd_curr->cmd_tokens = extract_tokens(shell->tokens, i);
		handle_heredoc(shell, cmd_curr, &cmd_curr->cmd_tokens);
		if (shell->interrupt)
		{
			shell->interrupt = false;
			return ;
		}
		cmd_curr = cmd_curr->next;
		i++;
	}
	handle_pipes(shell);
	shell->pipe_mode = false;
}
