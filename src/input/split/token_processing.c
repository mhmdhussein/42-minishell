/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:43:53 by mohhusse          #+#    #+#             */
/*   Updated: 2025/03/17 13:32:38 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_quoted_sequence(char *str, int *i, char *quote_char)
{
	if ((str[*i] == '\'' || str[*i] == '\"') && *quote_char == 0)
		*quote_char = str[*i];
	else if (str[*i] == *quote_char)
		*quote_char = 0;
}

int	handle_delimiter(char *str, int *i, char *token, int *j)
{
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
	{
		if (token)
		{
			token[(*j)++] = str[*i];
			token[(*j)++] = str[*i + 1];
			token[*j] = '\0';
		}
		(*i) += 2;
		return (2);
	}
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
	{
		if (token)
		{
			token[(*j)++] = str[*i];
			token[*j] = '\0';
		}
		(*i)++;
		return (1);
	}
	return (0);
}

int	process_and_count_token(char *str, int *i, char *token)
{
	int		len;
	char	quote_char;
	int		j;
	int		delim_len;

	len = 0;
	j = 0;
	quote_char = 0;
	delim_len = handle_delimiter(str, i, token, &j);
	if (delim_len > 0)
		return (delim_len);
	while (str[*i] != '\0')
	{
		handle_quoted_sequence(str, i, &quote_char);
		if (token)
			token[j++] = str[*i];
		len++;
		(*i)++;
		if (quote_char == 0 && (ft_isspace(str[*i])
				|| check_delimiter((char []){str[*i], '\0'})))
			break ;
	}
	if (token)
		token[j] = '\0';
	return (len);
}

char	*copy_token(char *str, int start)
{
	int		len;
	int		i;
	char	*token;

	i = start;
	len = process_and_count_token(str, &i, NULL);
	token = (char *)malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	i = start;
	process_and_count_token(str, &i, token);
	return (token);
}
