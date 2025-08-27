/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:48:47 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/17 14:59:51 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb > 4294967295 / size)
		return (NULL);
	p = malloc(nmemb * size);
	if (p)
		ft_bzero(p, nmemb * size);
	return (p);
}
