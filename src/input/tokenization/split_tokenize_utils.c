/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokenize_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 22:50:25 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/25 22:50:25 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	skip_delims(char const *s, int j, char delim)
{
	while (s[j] && s[j] == delim)
		j++;
	return (j);
}

int	token_end(char const *s, int j, char delim)
{
	int	quote;

	quote = 0;
	while (s[j])
	{
		if (s[j] == '\\' && s[j + 1])
		{
			j += 2;
			continue ;
		}
		quote = update_quote(s[j], quote);
		if (s[j] == delim && quote == 0)
			break ;
		j++;
	}
	return (j);
}

void	free_split_partial(char **split, int upto)
{
	int	k;

	if (!split)
		return ;
	k = 0;
	while (k < upto)
		free(split[k++]);
	free(split);
}

char	**push_token(char const *s, char **split, int *w, int *limit)
{
	split[*w] = create_word(s, limit[0], limit[1]);
	if (!split[*w])
	{
		free_split_partial(split, *w);
		return (NULL);
	}
	(*w)++;
	return (split);
}

char	**ft_split_token_2(char const *s, char c, char **split, int words)
{
	int	j;
	int	w;
	int	limit[2];

	j = 0;
	w = 0;
	while (w < words)
	{
		j = skip_delims(s, j, c);
		if (!s[j])
			break ;
		limit[0] = j;
		limit[1] = token_end(s, j, c);
		if (!push_token(s, split, &w, limit))
			return (NULL);
		if (s[limit[1]])
			j = limit[1] + 1;
		else
			j = limit[1];
	}
	split[w] = NULL;
	return (split);
}
