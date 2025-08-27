/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:38:44 by mohhusse          #+#    #+#             */
/*   Updated: 2025/06/12 22:38:44 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*cwd;

	shell->last_exit_status = 0;
	cwd = envget(shell->env, "PWD");
	if (!cwd)
		cwd = shell->current_pwd;
	if (cwd)
		printf("%s\n", cwd);
	else
		printf("pwd: error retrieving current directory: getcwd: cannot access"
			"parent directories: No such file or directory\n");
}
