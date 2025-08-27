/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:34:27 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/18 14:04:49 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_substr_helper(char *sub)
{
	if (!sub)
		return (NULL);
	*sub = '\0';
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char			*sub;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sub = (char *)malloc(sizeof(char) * 1);
		return (ft_substr_helper(sub));
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && *(s + start + i))
	{
		*(sub + i) = *(s + start + i);
		i++;
	}
	*(sub + i) = '\0';
	return (sub);
}
