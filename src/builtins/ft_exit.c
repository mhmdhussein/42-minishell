/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:11:22 by mohhusse          #+#    #+#             */
/*   Updated: 2025/03/17 13:51:01 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isnum(char *str)
{
	int		i;

	i = 0;
	while (*(str + i) == ' ' || *(str + i) == '\f' || *(str + i) == '\n'
		|| *(str + i) == '\r' || *(str + i) == '\t' || *(str + i) == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_range_nb(char *str, bool neg)
{
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	if (neg)
	{
		if (ft_strcmp(str, min) > 0)
			return (0);
		return (1);
	}
	else
	{
		if (ft_strcmp(str, max) > 0)
			return (0);
		return (1);
	}
}

int	check_exit_nb(char *str)
{
	int		i;
	bool	neg;

	i = 0;
	neg = false;
	while (*(str + i) == ' ' || *(str + i) == '\f' || *(str + i) == '\n'
		|| *(str + i) == '\r' || *(str + i) == '\t' || *(str + i) == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = true;
		i++;
	}
	if (ft_strlen(str + i) <= 18)
		return (1);
	else if (ft_strlen(str + i) > 19)
		return (0);
	else
		return (check_range_nb((str + i), neg));
}

void	ft_exit(t_cmd *cmd, t_shell *shell)
{
	shell->last_exit_status = 0;
	if (!shell->pipe_mode)
		printf("exit\n");
	if (cmd->args[1])
	{
		if (!ft_isnum(cmd->args[1]) || !check_exit_nb(cmd->args[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", cmd->args[1]);
			shell->last_exit_status = 2;
		}
		else if (cmd->args[2])
		{
			printf("bash: exit: too many arguments\n");
			shell->last_exit_status = 1;
			return ;
		}
		else
			shell->last_exit_status = ft_atoi(cmd->args[1]);
	}
	shell->running = false;
	exit(shell->last_exit_status);
}
