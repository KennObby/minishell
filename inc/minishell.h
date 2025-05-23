/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:01:37 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/22 11:31:08 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//< ----------------------- INCLUDES -------------------- >
# include <stdio.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>
# include "../Libft/libft.h"
# include "../Libft/ft_printf.h"
# include "../Libft/get_next_line_bonus.h"

extern int	g_status;

//< ----------------------- STRUCTS --------------------- >

/* 
 * CMD = combination of node like `echo "Hi"` -> args = ["echo", "Hi"];
 * WORD = tokens took in a CMD sequence like a catch-all non operations
 * PIPE = |
 * SEMICOLON = ;
 * LOGICAL_AND = &&
 * LOGICAL_OR = ||
 * REDIRECT_IN = <
 * REDIRECT_OUT = >
 * APPEND = >>
 * HEREDOC = <<
 * GROUPING = ( )
 * GROUPING_OPEN = opened parenthesis "(" (opener)
 * GROUPING_CLOSE = closed parenthesis ")" (closer)
 * END = end of token ? Not sure to be how to implement it but lets try
 */
typedef enum e_type
{
	CMD,
	WORD,
	PIPE,
	SEMICOLON,
	LOGICAL_AND,
	LOGICAL_OR,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	GROUPING,
	GROUPING_OPEN,
	GROUPING_CLOSE,
	END,
	NB_TYPES,
}				t_type;

/*
 * filename = stores regular redirs
 * fd = for HEREDOC (read-end of pipe)
 *
 */
typedef struct s_redir
{
	t_type	type;
	char	*filename;
	int		fd;
}				t_redir;

/*
 * key = environment variable name
 * value = file path dedicated to the key 
 * env => "key=value"
 *
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

/*
 * type = enum t_type
 * value = The actual string (e.g., "ls", "|")
 *
 */
typedef struct s_token
{
	t_type	type;
	char	*value;
	bool	has_no_space_after;
}				t_token;

/*
 * binary tree parser, identifying nodes by recursively trying to follow 
 * precedence of POSIX bash operators (e.g "|", "<<", etc...)
 *
 */
typedef struct s_parser
{
	t_token	*tokens;
	int		pos;
}				t_parser;

/* 
 * In case we need to update PWD (pwd) and OLDPWD (called by cd -)
 * We will probably need to use struct for pwd in the builtin_pwd() function
 * Otherwise, no need to use it 
 * cwd = current working directory
 * cwd_size =  size of cwd -> ref to PATH_MAX macro in limits.h
 *
 * typedef struct s_pwd
 *{
 *	char	*cwd;
 *	long	cwd_size;
 *}				t_pwd;
 *
 */

/*
 * DOCS: https://www.geeksforgeeks.org/binary-tree-in-c/ 
 *
 * type = type tokenized in a node, ref. to operation type
 * args = args in prompt
 * writer = left child => output provider. related STDOUT_FILENO
 * reader = right child => input provider. related STDIN_FILENO
 */
typedef struct s_node
{
	t_type			type;
	char			**args;
	t_redir			*redirs;
	int				redir_count;
	struct s_node	*writer;
	struct s_node	*reader;
}				t_node;

# define MAX_TOKENS 1024
# define MAX_ARGS 1024
# define MAX_PATH 1024
//< --------------------------- FUNCTIONS --------------------- >
//
//< --------------------------- BINARY TREE ------------------- >
//< --------------------------- init_tree.c ------------------- >
t_node		*create_leaf(char **args);
t_node		*create_node(t_type type, t_node *left, t_node *right);

//< --------------------------- bt_parser_utils.c ------------- >
t_type		peek(t_parser *parser);
void		consume(t_parser *parser);
int			is_redirection(t_type type);
void		print_syntax_error(t_parser *parser);
t_node		*parse(t_parser *parser);
bool		expect_valid_token(t_parser *parser);
bool		expect_token_and_consume(t_parser *parser, t_type expected);

//< -------------------------- bt_parser_helpers.c ------------ >
void		*handle_syntax_error(t_parser *parser);

//< --------------------------- bt_parser_redirs.c ------------ >
int			add_redirect(t_parser *parser, t_node *cmd_node, t_redir redir);
int			parse_redirects(t_parser *parser, t_node *cmd_node);

//< -------------------------- bt_parser_cmd.c ---------------- >
int			parse_single_redirect(t_parser *parser, t_node *cmd_node);
char		*merge_tokens(t_parser *parser);
char		**collect_args(t_parser *parser, t_node *cmd_node, int *arg_count);
int			finalize_args(t_node *cmd, char **args, int arg);
t_node		*parse_command(t_parser *parser);

//< --------------------------- bt_parser.c ------------------- >
t_node		*parse_semicolon(t_parser *parser);
t_node		*parse_logical(t_parser *parser);
t_node		*parse_pipeline(t_parser *parser);
t_node		*parse_grouping(t_parser *parser);
t_node		*parse(t_parser *parser);

//< --------------------------- bt_parser_args.c -------------- >
void		expand_node_args(t_node *node, t_env *env);

//< --------------------------- token.c ----------------------- >
t_token		create_token(t_type type, char *val);
int			tokenize_word(char *input, t_token *tokens, int i, int *pos);
t_token		*tokenize(char *input);
int			tokenize_operators(char *input, t_token *tokens, int i, int *pos);

//< --------------------------- token_utils.c ----------------- >
int			is_operator(char c);
bool		has_no_space_after(const char *input, int pos);
int			is_control_token(t_type type);
bool		should_merge(t_token prev, t_token next);

//< --------------------------- free_tree.c ------------------- >
void		free_tree(t_node *node);
void		free_tokens(t_token *tokens);
void		free_args(char **args, int count);

//< --------------------------- main.c ------------------------ >
char		*build_prompt(t_env *env);
void		remove_newline(char	*str);
void		inter_mode(t_env *env_list);
void		non_inter_mode(t_env *env_list);

//< --------------------------- to_str_helper.c --------------- >
const char	*redir_type_str(t_type type);
const char	*type_to_str(t_type type);
void		print_tree(t_node *node, int depth);

//< --------------------------- exec_utils.c ------------------ >
void		heredoc_sig_handler(int sig);

//< --------------------------- exec_ops.c -------------------- >
int			execute_cmd(t_node *cmd, t_env *env_list);
int			execute_pipe(t_node *pipe_node, t_env *env);
int			execute_logical(t_node *logical_node, t_env *env);
int			execute_semicolon(t_node *semi_node, t_env *env);
int			handle_redirections(t_node *cmd);

//< --------------------------- exec_mgmt.c ------------------- >
int			execute(t_node *node, t_env **env);
int			execute_forked_builtin(t_node *cmd, t_env **env);
int			execute_is_parent_only_builtin(t_node *cmd, t_env **env);
void		prepare_heredocs(t_node *node);
int			handle_heredoc(char *delimiter);

//< --------------------------- signal_handlers.c ------------- >
void		sigint_handler(int sig);
void		heredoc_sig_handler(int sig);
void		setup_signals(void);
void		reset_signals(void);

//< --------------------------- BUILT-INS --------------------- >
//< --------------------------- env_mgmt.c -------------------- >
t_env		*add_env_from_line(t_env *list, char *env_line);
char		*get_env_value(t_env *env, char *key);
char		*resolve_path(char *cmd, t_env *env);
void		update_or_add_env(t_env **env, const char *key, const char *value);
void		bump_shlvl(t_env *env);

//< --------------------------- env_init.c -------------------- >
t_env		*init_env_list(char **envp);
char		**env_list_to_array(t_env *env);
t_env		*copy_env(t_env *env);
void		sort_env(t_env *env);

//< --------------------------- free_env.c -------------------- >
void		free_env_list(t_env *env);
void		free_str_array(char **arr);

//< --------------------------- pwd.c ------------------------- >
int			builtin_pwd(void);

//< --------------------------- cd_mgmt.c --------------------- >
char		*handle_cd_path(t_node *cmd, t_env **env);
int			builtin_cd(t_node *cmd, t_env **env);

//< --------------------------- echo_mgmt.c ------------------- >
char		*handle_single_quotes(char *arg);
char		*extract_var_name(const char *s);
char		*ft_strjoin_free(char *s1, const char *s2);
char		*expand_double_quoted(const char *s, t_env **env);
char		*handle_double_quotes(char *arg, t_env **env);

//< --------------------------- export_mgmt.c ----------------- >
int			print_export(t_env *env);
int			builtin_export(t_node *cmd, t_env **env);

//< --------------------------- unset_mgmt.c ------------------ >
int			builtin_unset(t_node *cmd, t_env **env);

//< --------------------------- builtin_utils.c --------------- >
int			is_builtin(char *cmd);

//< --------------------------- builltin_mgmt.c --------------- >
int			builtin_env(t_env *env);
int			builtin_echo(t_node *cmd, t_env **env);
int			is_forkable_builtin(char *cmd);
int			is_parent_only_builtin(char *cmd);
int			exec_builtin(t_node *cmd, t_env **env);

#endif
