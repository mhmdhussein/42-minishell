/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:25:54 by mohhusse          #+#    #+#             */
/*   Updated: 2025/06/11 13:25:54 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	no_file_error(char *cmd, int *path_flag, t_shell *shell)
{
	*path_flag = 1;
	printf("bash: %s: No such file or directory\n", cmd);
	shell->last_exit_status = 127;
}

char	*check_absolute_relative_path(char *cmd, int *path_flag, t_shell *shell)
{
	struct stat	st;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			*path_flag = 1;
			printf("bash: %s: Is a directory\n", cmd);
			shell->last_exit_status = 126;
		}
		else if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		else if (access(cmd, F_OK) == 0)
		{
			*path_flag = 1;
			printf("bash: %s: Permission denied\n", cmd);
			shell->last_exit_status = 126;
		}
		else
			no_file_error(cmd, path_flag, shell);
	}
	return (NULL);
}

char	*join_full_path(char *dir, char *cmd)
{
	char	*new_dir;
	char	*full_path;

	new_dir = ft_strjoin(dir, "/");
	if (!new_dir)
		return (NULL);
	full_path = ft_strjoin(new_dir, cmd);
	free(new_dir);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*find_executable_path(char *cmd, t_shell *shell)
{
	char	**dirs;
	char	*path;
	char	*full_path;
	int		i;

	path = envget(shell->env, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	full_path = NULL;
	while (dirs[i])
	{
		full_path = join_full_path(dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_double_array(dirs);
	return (full_path);
}
