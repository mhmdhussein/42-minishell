/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:52:33 by mohhusse          #+#    #+#             */
/*   Updated: 2025/05/13 14:52:33 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_special_prompt(t_token *heredoc, t_shell *shell)
{
	char	*line;

	while (1)
	{
		write(shell->std_out, "> ", 2);
		line = readline("");
		if (!*line)
		{
			write(shell->std_out, "\n", 1);
			continue ;
		}
		if (!ft_strcmp(line, heredoc->next->value))
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	process_heredoc_special(t_token *heredoc, t_shell *shell)
{
	int		pipe_fd;
	char	*temp;

	temp = heredoc->next->value;
	heredoc->next->value = remove_quotes(heredoc->next->value);
	free(temp);
	pipe_fd = dup(STDOUT_FILENO);
	dup2(shell->std_out, STDOUT_FILENO);
	heredoc_special_prompt(heredoc, shell);
	dup2(pipe_fd, STDOUT_FILENO);
}

void	handle_heredoc_special(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			process_heredoc_special(curr, shell);
			curr = curr->next;
		}
		curr = curr->next;
	}
}

void	delete_remainder(t_token **redir, t_token **previous)
{
	t_token	*curr;
	t_token	*next;

	if (!redir || !(*redir))
		return ;
	curr = *redir;
	next = curr->next;
	if (!curr->next)
	{
		free(curr->value);
		free(curr);
		curr = NULL;
	}
	while (curr)
	{
		free(curr->value);
		free(curr);
		curr = next;
		if (next)
			next = next->next;
	}
	if (!curr)
		(*redir) = NULL;
	if ((*previous))
		(*previous)->next = NULL;
}

int	redirection_syntax(t_shell *shell)
{
	t_token	*curr;
	t_token	*prev;

	curr = shell->tokens;
	prev = NULL;
	while (curr)
	{
		if (is_red(curr) && (!curr->next || curr->next->type != WORD))
		{
			if (!curr->next)
				printf("bash: syntax error near unexpected token `newline'\n");
			else if (curr->next->type != WORD)
				printf("bash: syntax error near unexpected token `%s'\n",
					curr->next->value);
			delete_remainder(&curr, &prev);
			if (!curr && !prev)
				shell->tokens = NULL;
			handle_heredoc_special(shell);
			shell->last_exit_status = 2;
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}
