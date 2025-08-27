/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 22:23:38 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/25 22:23:38 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	update_quote(char c, int quote)
{
	if (c == '\'' && quote != 2)
	{
		if (quote == 1)
			quote = 0;
		else
			quote = 1;
	}
	if (c == '\"' && quote != 1)
	{
		if (quote == 2)
			quote = 0;
		else
			quote = 2;
	}
	return (quote);
}

int	word_count(char const *s, char c, int quote, int count)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i])
		{
			if (s[i] == '\\' && s[i + 1])
			{
				i += 2;
				continue ;
			}
			quote = update_quote(s[i], quote);
			if (s[i] == c && quote == 0)
				break ;
			i++;
		}
	}
	return (count);
}

char	*create_word(char const *s, int start, int end)
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

char	**ft_split_tokenize(char const *s, char c)
{
	char	**split;
	int		words;
	int		count;
	int		quote;

	quote = 0;
	count = 0;
	if (!s)
		return (NULL);
	words = word_count(s, c, quote, count);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	return (ft_split_token_2(s, c, split, words));
}
