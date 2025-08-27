/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:39:23 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/20 14:43:07 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_home(t_env *env, char *path, t_shell *shell)
{
	char	*home;
	char	*expanded;

	home = envget(env, "HOME");
	if (!home)
		home = shell->original_home;
	if (!home)
		return (NULL);
	expanded = ft_strjoin(home, (path + 1));
	return (expanded);
}

char	*slice_end(char *str)
{
	char	*end;
	char	*result;
	int		len;

	end = ft_strrchr(str, '/');
	if (!end)
		return (ft_strdup(str));
	len = ft_strlen(str) - ft_strlen(end);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, len);
	result[len] = '\0';
	return (result);
}

void	handle_dot(t_shell *shell, char *old_pwd, const char *path)
{
	if (!ft_strcmp((char *)path, ".."))
	{
		if (old_pwd)
		{
			envset(shell->env, "OLDPWD", old_pwd);
			old_pwd = slice_end(old_pwd);
			envset(shell->env, "PWD", old_pwd);
			free(shell->current_pwd);
			shell->current_pwd = ft_strdup(old_pwd);
		}
		if (access(old_pwd, F_OK) == 0)
			chdir(old_pwd);
		else
			printf("chdir: error retrieving current directory: getcwd: "
				"cannot access parent directories:"
				"No such file or directory\n");
		free(old_pwd);
	}
	else if (!ft_strcmp((char *)path, "."))
	{
		printf("chdir: error retrieving current directory: getcwd: "
			"cannot access parent directories:"
			"No such file or directory\n");
	}
	return ;
}

void	change_directory(t_env *env, t_shell *shell, const char *path)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		old_pwd = ft_strdup(envget(env, "PWD"));
		if (!ft_strcmp((char *)path, "..") || !ft_strcmp((char *)path, "."))
		{
			handle_dot(shell, old_pwd, path);
			free(old_pwd);
			return ;
		}
	}
	if (chdir(path) == -1)
	{
		printf("chdir: error while changing directory\n");
		shell->last_exit_status = 1;
	}
	else
		set_old_pwd(env, old_pwd, shell);
}

void	ft_cd(t_cmd *cmd, t_env *env, t_shell *shell)
{
	const char	*path;

	shell->last_exit_status = 0;
	if (cmd->args[0] && cmd->args[1] && cmd->args[2])
		return (printf("bash: cd: too many arguments\n"),
			shell->last_exit_status = 1, (void)0);
	path = cmd->args[1];
	if (!path)
		path = get_home(env, shell);
	else if (!ft_strcmp((char *)path, "-"))
		path = get_old_pwd(env, true, shell);
	else if (!ft_strcmp((char *)path, "--"))
		path = get_old_pwd(env, false, shell);
	if (!path || (cmd->args[1] && cmd->args[1][0] == '\0')
		|| (path && path[0] == '\0') || (path && !check_path(path, shell)))
		return ;
	change_directory(env, shell, path);
}
