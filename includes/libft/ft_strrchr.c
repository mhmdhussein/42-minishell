/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 18:20:07 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/19 18:06:09 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ch;

	ch = NULL;
	while (*s)
	{
		if (*s == (char) c)
			ch = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)ch);
}
