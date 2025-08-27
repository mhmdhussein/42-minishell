/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:33:59 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/22 16:26:38 by rtraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirections(t_shell *shell, t_cmd *cmd, t_token **tokens)
{
	process_redirections(shell, cmd, tokens);
	if (cmd->input_fd == -2)
		return (0);
	return (1);
}

void	expand_tilda(t_shell *shell)
{
	char	*home_path;
	t_token	*curr;
	char	*temp;

	home_path = envget(shell->env, "HOME");
	if (!home_path)
		home_path = shell->original_home;
	if (!home_path)
		return ;
	curr = shell->tokens;
	while (curr)
	{
		if (!ft_strcmp(curr->value, "~"))
		{
			free(curr->value);
			curr->value = ft_strdup(home_path);
		}
		else if (!ft_strncmp(curr->value, "~/", 2))
		{
			temp = curr->value;
			curr->value = ft_strjoin(home_path, (temp + 1));
			free(temp);
		}
		curr = curr->next;
	}
}

void	exec(t_shell *shell, char *input)
{
	shell->tokens = tokenize(input);
	if (!shell->tokens)
		return (shell->last_exit_status = 1, (void)0);
	expand_tilda(shell);
	expand_variables(&shell->tokens, shell);
	remove_null(&shell->tokens);
	if (!shell->tokens)
		return (shell->last_exit_status = 0, (void)0);
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	if (check_pipes(shell->tokens) == -1)
	{
		if (!redirection_syntax(shell))
		{
			free_dup_close(shell);
			return ;
		}
		printf("bash: syntax error near unexpected token `|'\n");
		shell->last_exit_status = 2;
	}
	else if (check_pipes(shell->tokens) == 1)
		exec_pipes(shell);
	else
		exec_cmd(shell);
	free_dup_close(shell);
}

void	run_shell(t_shell *shell)
{
	char	*input;

	while (shell->running)
	{
		input = readline("\033[37;42;1mminishell>\033[0m ");
		if (g_s > 0)
		{
			shell->last_exit_status = 130;
			g_s = 0;
		}
		if (!input)
		{
			printf("\nexit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			exec(shell, input);
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
	{
		printf("\033[37;41mminishell error:\033[0m"
			" No arguments should be provided.\n");
		return (1);
	}
	init_shell(&shell, envp);
	setupsignals();
	run_shell(&shell);
	free_env(shell.env);
	shell.env = NULL;
	free(shell.original_home);
	free(shell.current_pwd);
	return (shell.last_exit_status);
}
