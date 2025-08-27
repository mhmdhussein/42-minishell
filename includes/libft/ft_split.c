/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:35:51 by mohhusse          #+#    #+#             */
/*   Updated: 2025/01/25 15:41:33 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*ft_create_word(char const *s, int start, int end)
{
	int		i;
	char	*word;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i++] = s[start++];
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_split2(char const *s, char c, char **split, int words)
{
	int		i;
	int		start;
	int		j;

	i = 0;
	start = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		start = j;
		while (s[j] && s[j] != c)
			j++;
		if (j > start)
		{
			split[i++] = ft_create_word(s, start, j);
			if (!split[i - 1])
				return (NULL);
		}
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	return (ft_split2(s, c, split, words));
}
