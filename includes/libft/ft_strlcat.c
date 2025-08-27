/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:39:27 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/19 17:51:50 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const size_t	srclen = ft_strlen(src);
	const size_t	dstlen = ft_strnlen(dst, size);

	if (dstlen >= size)
		return (size + srclen);
	if (srclen < size - dstlen - 1)
		ft_memcpy(dst + dstlen, src, srclen + 1);
	else
	{
		if (size > dstlen)
		{
			ft_memcpy(dst + dstlen, src, size - dstlen - 1);
			dst[size - 1] = '\0';
		}
	}
	return (dstlen + srclen);
}
