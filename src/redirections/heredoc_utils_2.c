/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:56:11 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/22 16:13:32 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	filename_in_tokens(t_shell *shell, char *filename)
{
	t_token	*curr;

	curr = shell->tokens;
	while (curr)
	{
		if ((curr->type == OUT || curr->type == APPEND || curr->type == IN)
			&& !ft_strcmp(curr->next->value, filename))
			return (1);
		curr = curr->next;
	}
	return (0);
}

char	*create_tmp(t_shell *shell)
{
	char	*name;
	char	*tmp_name;

	name = (char *)malloc(sizeof(char) * 2);
	if (!name)
		return (NULL);
	name[0] = 'p';
	name[1] = '\0';
	tmp_name = ft_strjoin("/tmp/", name);
	free(name);
	name = tmp_name;
	while (access(name, F_OK) == 0 || filename_in_tokens(shell, name))
	{
		name = appendchar(name, 'p');
		if (!name)
			return (NULL);
	}
	return (name);
}

void	expand_heredoc_line(t_shell *shell, char *line, int tmp_fd)
{
	char	*expanded_line;

	expanded_line = expand_heredoc(line, shell);
	if (!expanded_line)
		expanded_line = ft_strdup("");
	write(tmp_fd, expanded_line, ft_strlen(expanded_line));
	free(expanded_line);
}

void	handle_line(t_shell *shell, bool expand, char *line, int tmp_fd)
{
	if (expand)
		expand_heredoc_line(shell, line, tmp_fd);
	else
		write(tmp_fd, line, ft_strlen(line));
	write(tmp_fd, "\n", 1);
	free(line);
}

void	heredoc_prompt(t_shell *shell, bool expand, int tmp_fd, char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(shell->std_out, "\n", 1);
			break ;
		}
		if (!*line)
		{
			write(tmp_fd, "\n", 1);
			free(line);
			continue ;
		}
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		handle_line(shell, expand, line, tmp_fd);
	}
}
