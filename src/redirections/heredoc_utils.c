/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:52:51 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/06 18:52:51 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_red(t_token *curr)
{
	return (curr->type == IN || curr->type == OUT || curr->type == APPEND
		|| curr->type == HEREDOC);
}

void	add_heredoc(char *filename, t_shell *shell)
{
	t_heredoc	*new_heredoc;

	new_heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!new_heredoc)
		return ;
	new_heredoc->filename = filename;
	new_heredoc->next = shell->heredocs;
	shell->heredocs = new_heredoc;
}

char	*remove_quotes_heredoc(char *value)
{
	char	*result;
	int		quote;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	quote = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' && quote == 0)
			quote = 1;
		else if ((value[i] == '\'' && quote == 1)
			|| (value[i] == '\"' && quote == 2))
			quote = 0;
		else if (value[i] == '\"' && quote == 0)
			quote = 2;
		else if (!(value[i] == '$' && (value[i + 1] == '\"'
					|| value[i + 1] == '\'')
				&& quote == 0 && (i == 0 || value[i - 1] != '$')))
			result = appendchar(result, value[i]);
		i++;
	}
	return (result);
}

void	heredoc_to_in(t_token **heredoc, char *tmpfile)
{
	free((*heredoc)->value);
	(*heredoc)->value = ft_strdup("<");
	(*heredoc)->type = IN;
	free((*heredoc)->next->value);
	(*heredoc)->next->value = ft_strdup(tmpfile);
}

void	close_heredoc(t_cmd **cmd, char *tmpfile, int pipe_fd, int tmp_fd)
{
	if ((*cmd)->input_fd != -1)
		close((*cmd)->input_fd);
	(*cmd)->input_fd = open(tmpfile, O_RDONLY);
	if ((*cmd)->input_fd == -1)
		return ;
	dup2(pipe_fd, STDOUT_FILENO);
	close(tmp_fd);
}
