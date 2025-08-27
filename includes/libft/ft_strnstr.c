/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:59:56 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/17 16:38:10 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	j = 0;
	while (j < len && *(big + j))
	{
		i = 0;
		while (*(little + i) && (j + i) < len && *(big + j + i)
			&& *(little + i) == *(big + j + i))
			i++;
		if (i == little_len)
			return ((char *)(big + j));
		j++;
	}
	return (NULL);
}
