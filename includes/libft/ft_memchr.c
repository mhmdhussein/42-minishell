/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:40:42 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/17 16:37:11 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*p = (const unsigned char *) s;
	size_t					i;

	i = 0;
	while (i < n)
	{
		if (*(p + i) == (unsigned char)c)
			return ((void *)(p + i));
		i++;
	}
	return (NULL);
}
