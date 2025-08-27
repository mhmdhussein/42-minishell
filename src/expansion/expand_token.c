/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:33:15 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/26 14:20:56 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_variable_name(char *value, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	len = 0;
	if (!is_var_char(value[start], 1))
		return (NULL);
	while (value[start + len] && is_var_char(value[start + len], 0))
		len++;
	var_name = ft_substr(value, start, len);
	*i += len - 1;
	return (var_name);
}

char	*handle_variable2(char *value, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_variable_name(value, i);
	if (!var_name)
		return (ft_strdup(""));
	var_value = envget(shell->env, var_name);
	free(var_name);
	if (var_value && !(ft_strchr(var_value, '\'')
			|| ft_strchr(var_value, '\"')))
		return (ft_strdup(var_value));
	else if (var_value && (ft_strchr(var_value, '\'')
			|| ft_strchr(var_value, '\"')))
		return (keep_quotations(var_value));
	else
		return (ft_strdup(""));
}

char	*handle_variable(char *value, int *i, t_shell *shell, int quote)
{
	if ((value[(*i) + 1] == '\"' || value[(*i) + 1] == '\'') && quote == 0)
		return (ft_strdup(""));
	else if ((value[(*i) + 1] == '\"' || value[(*i) + 1] == '\'') && quote == 2)
		return (ft_strdup("$"));
	if (value[(*i) + 1] == ':' || value[(*i) + 1] == '=')
		return (ft_strdup("$"));
	(*i)++;
	if (value[*i] == '$')
		return (ft_strdup("42"));
	else if (value[*i] == '?')
		return (ft_itoa(shell->last_exit_status));
	else if (!is_var_char(value[*i], 1))
		return (ft_strdup(""));
	return (handle_variable2(value, i, shell));
}

char	*append_variable(char *result, char *expanded)
{
	char	*temp;

	temp = result;
	if (expanded)
	{
		result = ft_strjoin(result, expanded);
		free(temp);
	}
	return (result);
}

char	*expand_token(char *value, t_shell *shell)
{
	int		i;
	int		quote;
	char	*result;
	char	*expanded;

	i = 0;
	quote = 0;
	result = ft_strdup("");
	while (value[i])
	{
		check_quotes(value[i], &quote);
		if (value[i] == '$' && (quote == 0 || quote == 2)
			&& value[i + 1] && value[i + 1] != ' ')
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
