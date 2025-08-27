/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:55:53 by mohhusse          #+#    #+#             */
/*   Updated: 2025/03/17 13:17:48 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (true);
	else if (!ft_strcmp(cmd, "cd"))
		return (true);
	else if (!ft_strcmp(cmd, "pwd"))
		return (true);
	else if (!ft_strcmp(cmd, "export"))
		return (true);
	else if (!ft_strcmp(cmd, "unset"))
		return (true);
	else if (!ft_strcmp(cmd, "env"))
		return (true);
	else if (!ft_strcmp(cmd, "exit"))
		return (true);
	else
		return (false);
}

void	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, shell->env, shell);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(shell->env, shell);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, shell);
}
