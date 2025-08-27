/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:53:36 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/18 14:03:17 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(long n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_itoa2(char *num)
{
	num = (char *)malloc(sizeof(char) * 2);
	if (!num)
		return (NULL);
	num[0] = '0';
	num[1] = '\0';
	return (num);
}

char	*ft_itoa(int n)
{
	long	a;
	char	*num;
	size_t	len;

	a = n;
	len = ft_len(a);
	num = NULL;
	if (a == 0)
		return (ft_itoa2(num));
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len--] = '\0';
	if (a < 0)
	{
		num[0] = '-';
		a = -a;
	}
	while (a > 0)
	{
		num[len] = a % 10 + '0';
		a /= 10;
		len--;
	}
	return (num);
}
