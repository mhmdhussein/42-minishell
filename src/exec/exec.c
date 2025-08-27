/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:16:49 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/26 19:02:58 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_child_process(t_cmd *cmd, t_shell *shell, char *full_path)
{
	char	**env_array;

	restoresignals();
	env_array = env_to_array(shell->env);
	execve(full_path, cmd->args, env_array);
	perror("execve");
	free_double_array(env_array);
	shell->last_exit_status = 1;
	exit(shell->last_exit_status);
}

static void	wait_for_child(pid_t pid, t_shell *shell)
{
	int		status;
	int		sig;

	ignoresignals();
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			shell->last_exit_status = 130;
			write(STDOUT_FILENO, "\n", 1);
			setupsignals();
			return ;
		}
		else if (sig == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit\n", 5);
			shell->last_exit_status = 131;
			setupsignals();
			return ;
		}
	}
	setupsignals();
	shell->last_exit_status = WEXITSTATUS(status);
}

void	fork_command(t_shell *shell, t_cmd *cmd, char *full_path)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, shell, full_path);
	else if (pid > 0)
		wait_for_child(pid, shell);
	free(full_path);
}

void	execute_command(t_cmd *cmd, t_shell *shell)
{
	char	*full_path;
	int		path_flag;

	path_flag = 0;
	full_path = check_absolute_relative_path(cmd->args[0], &path_flag, shell);
	if (!envget(shell->env, "PATH") && path_flag == 0 && !full_path)
		no_file_error(cmd->args[0], &path_flag, shell);
	if (path_flag == 1)
		return ;
	if (!full_path)
		full_path = find_executable_path(cmd->args[0], shell);
	if (!full_path || cmd->args[0][0] == '\0' || !ft_strcmp(cmd->args[0], ".")
		|| !ft_strcmp(cmd->args[0], ".."))
	{
		dup2(shell->std_out, STDOUT_FILENO);
		printf("bash: %s: command not found\n", cmd->args[0]);
		shell->last_exit_status = 127;
		if (full_path)
			free(full_path);
		return ;
	}
	fork_command(shell, cmd, full_path);
}

void	exec_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = init_cmd(shell);
	if (!cmd || !redirection_syntax(shell))
		return ;
	if (shell->tokens && shell->cmds->input_fd != -2)
	{
		cmd->next = NULL;
		handle_heredoc(shell, cmd, &shell->tokens);
		if (shell->interrupt)
		{
			shell->interrupt = false;
			return ;
		}
		if (!redirections(shell, shell->cmds, &shell->tokens))
			return ;
		if (shell->tokens)
		{
			cmd->args = detokenize(shell->tokens);
			if (is_builtin(cmd->args[0]))
				exec_builtin(cmd, shell);
			else
				execute_command(cmd, shell);
		}
	}
}
