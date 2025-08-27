/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:41:54 by mohhusse          #+#    #+#             */
/*   Updated: 2025/03/17 11:43:24 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_tokens(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_isspace(str[i]))
			i++;
		if (str[i] != '\0')
		{
			process_and_count_token(str, &i, NULL);
			count++;
		}
	}
	return (count);
}

void	process_input(char *str, int *ij, char **tokens)
{
	int		token_start;

	token_start = ij[0];
	if ((str[ij[0]] == '<' && str[ij[0] + 1] != '\0' && str[ij[0] + 1] == '<')
		|| (str[ij[0]] == '>' && str[ij[0] + 1] != '\0'
			&& str[ij[0] + 1] == '>'))
	{
		ij[0] += 2;
		tokens[ij[1]++] = copy_token(str, token_start);
	}
	else if (check_delimiter((char []){str[ij[0]], '\0'}))
	{
		ij[0]++;
		tokens[ij[1]++] = copy_token(str, token_start);
	}
	else
	{
		tokens[ij[1]++] = copy_token(str, token_start);
		process_and_count_token(str, &ij[0], NULL);
	}
}

char	**split_input(char *str)
{
	char	**tokens;
	int		ij[2];

	if (input_has_unmatched_quotes(str))
	{
		printf("\033[37;41mminishell error:\033[0m '\033[33;3;1m%s\033[0m':"
			" Input has unmatched quotes\n", str);
		return (NULL);
	}
	tokens = (char **)malloc(sizeof(char *) * (count_tokens(str) + 1));
	if (!tokens)
		return (NULL);
	ij[0] = 0;
	ij[1] = 0;
	while (str[ij[0]] != '\0')
	{
		while (str[ij[0]] != '\0' && ft_isspace(str[ij[0]]))
			ij[0]++;
		if (str[ij[0]] != '\0')
			process_input(str, ij, tokens);
	}
	tokens[ij[1]] = NULL;
	return (tokens);
}
