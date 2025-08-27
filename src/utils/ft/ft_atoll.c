/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:07:24 by mohhusse          #+#    #+#             */
/*   Updated: 2025/05/12 16:07:24 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

long long	ft_atoll(const char *nptr)
{
	long long	sign;
	long long	i;
	long long	result;

	sign = 1;
	i = 0;
	result = 0;
	while (*(nptr + i) == ' ' || *(nptr + i) == '\f' || *(nptr + i) == '\n'
		|| *(nptr + i) == '\r' || *(nptr + i) == '\t' || *(nptr + i) == '\v')
	{
		i++;
	}
	if (*(nptr + i) == '-' || *(nptr + i) == '+')
	{
		if (*(nptr + i) == '-')
			sign *= -1;
		i++;
	}
	while (*(nptr + i) && *(nptr + i) >= '0' && *(nptr + i) <= '9')
	{
		result = result * 10;
		result = result + (*(nptr + i) - '0');
		i++;
	}
	return (sign * result);
}
