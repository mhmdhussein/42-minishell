/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:24:48 by mohhusse          #+#    #+#             */
/*   Updated: 2025/01/25 14:35:31 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*token_start;

	if (str)
		next_token = str;
	if (!next_token)
		return (NULL);
	while (*next_token && ft_strchr(delim, *next_token))
		next_token++;
	if (*next_token == '\0')
		return (NULL);
	token_start = next_token;
	while (*next_token && !ft_strchr(delim, *next_token))
		next_token++;
	if (*next_token)
	{
		*next_token = '\0';
		next_token++;
	}
	else
		next_token = NULL;
	return (token_start);
}
