/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:33:16 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/18 14:04:44 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (*(s1 + start) && ft_is_in_set(*(s1 + start), set))
		start++;
	end = ft_strlen(s1);
	while (start < end && ft_is_in_set(*(s1 + end - 1), set))
		end--;
	trim = (char *)malloc((end - start + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	ft_memcpy(trim, s1 + start, end - start);
	*(trim + end - start) = '\0';
	return (trim);
}
