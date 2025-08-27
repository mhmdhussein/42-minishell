/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:51:38 by mohhusse          #+#    #+#             */
/*   Updated: 2025/05/14 14:53:41 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

int	check_delimiter(char *str)
{
	return (str[0] == '>' || str[0] == '<' || str[0] == '|'
		|| (str[0] == '<' && str[1] == '<')
		|| (str[0] == '>' && str[1] == '>') || ft_isspace(str[0]));
}

bool	input_has_unmatched_quotes(char *str)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"') && current_quote == 0)
			current_quote = str[i];
		else if (str[i] == current_quote)
			current_quote = 0;
		i++;
	}
	return (current_quote != 0);
}

char	*remove_quotes(char *value)
{
	char	*result;
	int		quote;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	quote = 0;
	i = -1;
	while (value[++i])
	{
		if (value[i] == '\\' && (value[i + 1] == '\'' || value[i + 1] == '\"'
				|| value[i + 1] == '\\'))
			result = appendchar(result, value[++i]);
		else if (value[i] == '\'' && quote == 0)
			quote = 1;
		else if ((value[i] == '\'' && quote == 1)
			|| (value[i] == '\"' && quote == 2))
			quote = 0;
		else if (value[i] == '\"' && quote == 0)
			quote = 2;
		else
			result = appendchar(result, value[i]);
	}
	return (result);
}
