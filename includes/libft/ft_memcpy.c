/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:20:57 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/19 17:58:01 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char			*s;
	char				*d;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (NULL);
	s = (const char *)src;
	d = (char *)dest;
	i = 0;
	while (i < n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (dest);
}
