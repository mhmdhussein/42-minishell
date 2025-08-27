/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 22:58:26 by mohhusse          #+#    #+#             */
/*   Updated: 2025/06/09 22:58:26 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_old_pwd(t_env *env, char *old_pwd, t_shell *shell)
{
	envset(env, "OLDPWD", old_pwd);
	free(old_pwd);
	old_pwd = getcwd(NULL, 0);
	if (old_pwd)
	{
		envset(env, "PWD", old_pwd);
		free(shell->current_pwd);
		shell->current_pwd = ft_strdup(old_pwd);
		free(old_pwd);
	}
}

int	check_path(const char *path, t_shell *shell)
{
	struct stat	st;

	if (!path)
		return (0);
	else if (access(path, F_OK) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		shell->last_exit_status = 1;
		return (0);
	}
	else if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		printf("bash: cd: %s: Not a directory\n", path);
		shell->last_exit_status = 1;
		return (0);
	}
	return (1);
}

char	*get_old_pwd(t_env *env, bool print, t_shell *shell)
{
	char		*path;

	path = envget(env, "OLDPWD");
	if (!path)
	{
		printf("cd: OLDPWD not set\n");
		shell->last_exit_status = 1;
		return (NULL);
	}
	else if (!check_path(path, shell))
		return (NULL);
	if (print)
		printf("%s\n", path);
	return (path);
}

char	*get_home(t_env *env, t_shell *shell)
{
	t_env	*home;

	home = env;
	while (home && ft_strcmp(home->key, "HOME") != 0)
		home = home->next;
	if (home && home->value && home->equal == true)
		return (home->value);
	else
	{
		printf("cd: HOME not set\n");
		shell->last_exit_status = 1;
		return (NULL);
	}
}
