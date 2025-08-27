/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:58:19 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/20 13:50:16 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_env(t_shell *shell)
{
	addenv2(&shell->env, "_", "/usr/bin/env");
	addenv2(&shell->env, "PWD", getcwd(NULL, 0));
	addenv2(&shell->env, "SHLVL", "0");
}

/*
imports env and transforms it into a linked list
*/
void	init_env(t_shell *shell, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*new_env;

	if (!envp || !*(envp))
	{
		set_env(shell);
		return ;
	}
	i = -1;
	while (envp[++i])
	{
		key = ft_strtok(envp[i], "=");
		value = ft_strtok(NULL, "");
		new_env = create_env(key, value);
		if (!new_env)
			return ;
		if (value)
			new_env->equal = true;
		else
			new_env->equal = false;
		new_env->next = shell->env;
		shell->env = new_env;
	}
}

/*
initializes shell and env

original home: when using "cd ~", it searches env
and if not found, it uses original home
*/
void	init_shell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->cmds = NULL;
	shell->tokens = NULL;
	shell->heredocs = NULL;
	shell->running = true;
	shell->interrupt = false;
	shell->last_exit_status = 0;
	shell->pipe_mode = false;
	init_env(shell, envp);
	if (envget(shell->env, "HOME") == NULL)
		shell->original_home = NULL;
	else
		shell->original_home = ft_strdup(envget(shell->env, "HOME"));
	if (!envget(shell->env, "PWD"))
		addenv2(&shell->env, "PWD", getcwd(NULL, 0));
	shell->current_pwd = ft_strdup(envget(shell->env, "PWD"));
	if (!envget(shell->env, "OLDPWD"))
		addenv2(&shell->env, "OLDPWD", NULL);
	increment_shlvl(shell);
}

t_cmd	*init_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->cmd_tokens = NULL;
	cmd->delim = NULL;
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	shell->cmds = cmd;
	return (cmd);
}
