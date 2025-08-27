/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:06:21 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/17 16:38:44 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t			len;
	char			*dup;

	len = ft_strlen(s) + 1;
	dup = malloc(len);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	return (dup);
}
