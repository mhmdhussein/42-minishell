/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:02:59 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/15 20:22:24 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	result;

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
