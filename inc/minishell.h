/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:01:37 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/25 10:04:49 by oilyine-         ###   ########.fr       */
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
# include "../Libft/libft.h"
# include "../Libft/ft_printf.h"
# include "../Libft/get_next_line_bonus.h"

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
}				t_type;

/*
 * type = enum t_type
 * value = The actual string (e.g., "ls", "|")
 *
 */
typedef struct s_token
{
	t_type	type;
	char	*value;
}				t_token;

/*
 * binary tree parser, identifying nodes by recursively trying to follow 
 * precedence POSIX bash operators (e.g "|", "<<", etc...)
 *
 */
typedef struct s_parser
{
	t_token	*tokens;
	int		pos;
}				t_parser;

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
t_node		*parse(t_parser *parser);

//< --------------------------- bt_parser.c ------------------- >
t_node		*parse_semicolon(t_parser *parser);
t_node		*parse_logical(t_parser *parser);
void		parse_redirects(t_parser *parser, t_node *cmd_node);
t_node		*parse_pipeline(t_parser *parser);
t_node		*parse_command(t_parser *parser);
t_node		*parse_grouping(t_parser *parser);

//< --------------------------- token.c ----------------------- >
int			is_operator(char c);
t_token		*tokenize(char *input);

//< --------------------------- free_tree.c ------------------- >
void		free_tree(t_node *node);
void		free_tokens(t_token *tokens);

//< --------------------------- main.c ------------------------ >
char		*build_prompt(t_env *env);
void		print_tree(t_node *node, int depth);

//< --------------------------- to_str_helper.c --------------- >
const char	*redir_type_str(t_type type);
const char	*type_to_str(t_type type);

//< --------------------------- exec_ops.c -------------------- >
int			execute_cmd(t_node *cmd, t_env *env_list);
int			execute_pipe(t_node *pipe_node, t_env *env);
int			execute_logical(t_node *logical_node, t_env *env);
int			execute_semicolon(t_node *semi_node, t_env *env);
int			handle_redirections(t_node *cmd);

//< --------------------------- exec_mgmt.c ------------------- >
int			execute(t_node *node, t_env **env);
void		prepare_heredocs(t_node *node);
int			handle_heredoc(char *delimiter);

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

//< --------------------------- free_env.c -------------------- >
void		free_env_list(t_env *env);
void		free_str_array(char **paths);

//< --------------------------- pwd.c ------------------------- >
int			builtin_pwd(void);

//< --------------------------- cd_mgmt.c --------------------- >
char		*handle_cd_path(t_node *cmd, t_env **env);
int			builtin_cd(t_node *cmd, t_env **env);

//< --------------------------- builtin_utils.c --------------- >
int			is_builtin(char *cmd);

//< --------------------------- builltin_mgmt.c --------------- >
int			builtin_env(t_env *env);
int			builtin_echo(t_node *cmd);
int			is_forkable_bultin(char *cmd);
int			is_parent_only_builtin(char *cmd);
int			exec_builtin(t_node *cmd, t_env **env);

#endif
