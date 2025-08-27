/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:38:06 by mohhusse          #+#    #+#             */
/*   Updated: 2025/08/20 13:55:53 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_s;

// ~~~~~~~~~~ Structs ~~~~~~~~~~

typedef struct s_heredoc
{
	char				*filename;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_env
{
	char			*key;
	bool			equal;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	ENV_VAR
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	int				input_fd;
	int				output_fd;
	bool			append;
	char			*delim;
	t_token			*cmd_tokens;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env		*env;
	t_cmd		*cmds;
	t_token		*tokens;
	t_heredoc	*heredocs;
	bool		running;
	bool		interrupt;
	int			last_exit_status;
	int			std_out;
	int			std_in;
	bool		pipe_mode;
	char		*original_home;
	char		*current_pwd;
}	t_shell;

// ~~~~~~~~~~ Init ~~~~~~~~~~
void			init_shell(t_shell *shell, char **envp);
void			init_env(t_shell *shell, char **envp);
t_cmd			*init_cmd(t_shell *shell);

// ~~~~~~~~~~ Input ~~~~~~~~~~
char			**split_input(char *str);
bool			input_has_unmatched_quotes(char *str);
int				ft_isspace(char c);
int				process_and_count_token(char *str, int *i, char *token);
char			*copy_token(char *str, int start);
int				check_delimiter(char *str);
char			*remove_quotes(char *value);
int				count_tokens(char *str);

// ~~~~~~~~~~ Tokenization ~~~~~~~~~~
t_token			*tokenize(char *input);
t_token			*split_tokenize(char *input);
void			revert_var(t_token	**tokens);
char			**detokenize(t_token *tokens);
t_token			*create_token(char *split);
void			add_token(t_token **head, t_token **newnode);
t_token_type	determine_token_type(char *value);
int				counttokens(t_token *tokens);
void			remove_null(t_token **tokens);
void			split_token(t_token **prev, t_token **curr, t_token **tokens);
char			**ft_split_tokenize(char const *s, char c);
char			**ft_split_token_2(char const *s, char c, char **split,
					int words);
char			*create_word(char const *s, int start, int end);
int				update_quote(char c, int quote);

// ~~~~~~~~~~ Expansion ~~~~~~~~~~
void			check_quotes(char c, int *quote);
char			*appendchar(char *str, char c);
void			expand_variables(t_token **tokens, t_shell *shell);
int				is_var_char(char c, int first);
char			*expand_token(char *value, t_shell *shell);
char			*keep_quotations(char *value);
char			*handle_variable(char *value, int *i, t_shell *shell,
					int quote);
char			*expand_heredoc(char *value, t_shell *shell);
char			*append_variable(char *result, char *expanded);

// ~~~~~~~~~~ Execution ~~~~~~~~~~
void			exec_builtin(t_cmd *cmd, t_shell *shell);
bool			is_builtin(char *cmd);
void			execute_command(t_cmd *cmd, t_shell *shell);
void			exec_cmd(t_shell *shell);
char			*find_executable_path(char *cmd, t_shell *shell);
char			*handle_dollar_quote_dollar(t_env *env);
char			*check_absolute_relative_path(char *cmd, int *path_flag,
					t_shell *shell);
void			no_file_error(char *cmd, int *path_flag, t_shell *shell);

// ~~~~~~~~~~ Redirections ~~~~~~~~~~
int				redirections(t_shell *shell, t_cmd *cmd, t_token **tokens);
void			process_redirections(t_shell *shell, t_cmd *cmd,
					t_token **tokens);
void			handle_heredoc(t_shell *shell, t_cmd *cmd, t_token **tokens);
int				redirection_syntax(t_shell *shell);
void			process_heredoc_special(t_token *heredoc, t_shell *shell);
char			*create_tmp(t_shell *shell);
void			add_heredoc(char *filename, t_shell *shell);
char			*remove_quotes_heredoc(char *value);
void			heredoc_to_in(t_token **heredoc, char *tmpfile);
void			close_heredoc(t_cmd **cmd, char *tmpfile,
					int pipe_fd, int tmp_fd);
void			heredoc_prompt(t_shell *shell, bool expand,
					int tmp_fd, char *delim);
int				is_red(t_token *curr);

// ~~~~~~~~~~ Pipes ~~~~~~~~~~
void			exec_pipes(t_shell *shell);
int				check_pipes(t_token *tokens);
void			parse_commands(t_token	*tokens, t_shell *shell);
void			handle_pipes(t_shell *shell);
t_token			*extract_tokens(t_token *tokens, int i);

// ~~~~~~~~~~ Builtins ~~~~~~~~~~
// cd
void			ft_cd(t_cmd *cmd, t_env *env, t_shell *shell);
char			*get_home(t_env *env, t_shell *shell);
char			*get_old_pwd(t_env *env, bool print, t_shell *shell);
int				check_path(const char *path, t_shell *shell);
void			set_old_pwd(t_env *env, char *old_pwd, t_shell *shell);
// echo
void			ft_echo(t_cmd *cmd, t_shell *shell);
// env
void			ft_env(t_env *env, t_shell *shell);
// exit
void			ft_exit(t_cmd *cmd, t_shell *shell);
// export
void			ft_export(t_cmd *cmd, t_shell *shell);
void			export_arg(char *assign, t_shell *shell);
// pwd
void			ft_pwd(t_shell *shell);
// unset
void			ft_unset(t_cmd *cmd, t_shell *shell);

// ~~~~~~~~~~ Env ~~~~~~~~~~
void			envset(t_env *env, char *key, char *value);
char			*envget(t_env *env, char *key);
void			addenv(t_env *env, char *key, char *value);
void			addenv2(t_env **env, char *key, char *value);
t_env			*create_env(char *key, char *value);
char			**env_to_array(t_env *env);

// ~~~~~~~~~~ Utils ~~~~~~~~~~
int				ft_strcmp(char *str1, char *str2);
char			*ft_strtok(char *str, const char *delim);
t_env			*merge_sort(t_env *env);
long long		ft_atoll(const char *nptr);

// ~~~~~~~~~~ Free ~~~~~~~~~~
void			free_double_array(char **array);
void			free_tokens(t_token *head);
void			free_env(t_env *env);
void			free_cmds(t_cmd *cmds);
void			free_dup_close(t_shell *shell);
void			free_pipe_child(t_shell *shell);
void			free_heredocs(t_heredoc *heredocs);

// ~~~~~~~~~~ Shell ~~~~~~~~~~
void			increment_shlvl(t_shell *shell);
void			decrement_shlvl(t_shell *shell);

// ~~~~~~~~~~ Signals ~~~~~~~~~~
void			handle_sigint(int sig);
void			setupsignals(void);
void			restoresignals(void);
void			ignoresignals(void);
void			restoresignals_heredoc(void);

#endif
