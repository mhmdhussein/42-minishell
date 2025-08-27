/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:59:25 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/26 14:28:19 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_heredoc(char *value, t_shell *shell)
{
	int		i;
	int		quote;
	char	*result;
	char	*expanded;

	i = 0;
	quote = 2;
	result = ft_strdup("");
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && value[i + 1] != ' ')
		{
			expanded = handle_variable(value, &i, shell, quote);
			result = append_variable(result, expanded);
			free(expanded);
		}
		else
			result = appendchar(result, value[i]);
		i++;
	}
	if (result[0] == '\0')
		return (free(result), NULL);
	return (result);
}

void	check_quotes(char c, int *quote)
{
	if (c == '"' && *quote != 1)
	{
		if (*quote == 2)
			*quote = 0;
		else
			*quote = 2;
	}
	else if (c == '\'' && *quote != 2)
	{
		if (*quote == 1)
			*quote = 0;
		else
			*quote = 1;
	}
}

char	*appendchar(char *str, char c)
{
	char	char_str[2];
	char	*temp;

	if (!str)
		return (NULL);
	char_str[0] = c;
	char_str[1] = '\0';
	temp = str;
	str = ft_strjoin(str, char_str);
	free(temp);
	return (str);
}

int	is_var_char(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

char	*keep_quotations(char *value)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"' || value[i] == '\\')
			result = appendchar(result, '\\');
		result = appendchar(result, value[i]);
		i++;
	}
	return (result);
}
