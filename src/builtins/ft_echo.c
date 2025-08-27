/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:39:16 by mohhusse          #+#    #+#             */
/*   Updated: 2025/06/12 22:39:16 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_newline_option(char *str)
{
	int		i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	ft_echo(t_cmd *cmd, t_shell *shell)
{
	bool	newline;
	int		i;

	newline = true;
	i = 1;
	while (cmd->args[i] && is_newline_option(cmd->args[i]))
	{
		newline = false;
		i++;
	}
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
			printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->last_exit_status = 0;
}
