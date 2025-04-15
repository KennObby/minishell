/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembo    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:04:50 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/30 22:40:33 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdlib.h>

t_node	*parse_semicolon(t_parser *parser)
{
	t_node	*left;
	t_node	*right;

	left = parse_logical(parser);
	if (peek(parser) == SEMICOLON)
	{
		consume(parser);
		right = parse_semicolon(parser);
		if (!right)
			return (left);
		return (create_node(SEMICOLON, left, right));
	}
	return (left);
}

t_node	*parse_logical(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_type	op;

	left = parse_pipeline(parser);
	while (peek(parser) == LOGICAL_AND || peek(parser) == LOGICAL_OR)
	{
		op = peek(parser);
		consume(parser);
		right = parse_logical(parser);
		left = create_node(op, left, right);
	}
	return (left);
}

t_node	*parse_pipeline(t_parser *parser)
{
	t_node	*left;
	t_node	*right;

	left = parse_grouping(parser);
	if (peek(parser) == PIPE)
	{
		consume(parser);
		right = parse_pipeline(parser);
		return (create_node(PIPE, left, right));
	}
	return (left);
}

/*
 * 1. Collecting commands by allocating based on MAX_ARGS size
 * 2. Collecting tokens until an operator is found
 * 3. Creating a leaf based on that node
 * 4. Attach redirections if any
 *
 * UPDATE: Adding the should_merge func()
 * The main idea is to detect that two tokens should be merged
 * if its the case, we join them 
 * (e.g echo "$HO''ME" -> $HOME)
 */
t_node	*parse_command(t_parser *parser)
{
	char		**args;
	int			arg_count;
	char		*merged;
	char		**new_args;
	t_node		*cmd_node;
	char		*tmp;

	arg_count = 0;
	args = NULL;
	while (parser->pos < MAX_TOKENS
		&& parser->tokens[parser->pos].type == WORD)
	{
		merged = ft_strdup(parser->tokens[parser->pos].value);
		if (!merged)
		{
			free_args(args, arg_count);
			return (NULL);
		}
		parser->pos++;
		while (parser->pos < MAX_TOKENS
			&& should_merge(parser->tokens[parser->pos - 1],
				parser->tokens[parser->pos]))
		{
			tmp = merged;
			merged = ft_strjoin(merged, parser->tokens[parser->pos].value);
			free(tmp);
			if (!merged)
			{
				free_args(args, arg_count);
				return (NULL);
			}
			parser->pos++;
		}
		new_args = ft_realloc(args, arg_count * sizeof(char *),
				(arg_count + 1) * sizeof(char *));
		if (!new_args)
		{
			free(merged);
			free_args(args, arg_count);
			return (NULL);
		}
		args = new_args;
		args[arg_count++] = merged;
	}
	new_args = ft_realloc(args, arg_count * sizeof(char *),
			(arg_count + 1) * sizeof(char *));
	if (!new_args)
	{
		free_args(args, arg_count);
		return (NULL);
	}
	args = new_args;
	args[arg_count] = NULL;
	if (arg_count == 0 && !is_redirection(peek(parser)))
	{
		ft_printf("bash: syntax error near unexpected token `%s`\n",
			parser->tokens[parser->pos].value);
		parser->pos = MAX_TOKENS;
		free(args);
		return (NULL);
	}
	cmd_node = create_leaf(args);
	if (!cmd_node)
		return (NULL);
	if (!parse_redirects(parser, cmd_node))
	{
		free_tree(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}

/* 1. Check si le token suivant est une redirection
 * 2. Assignation du type de redir
 * 3. Le filename devient la valeur du token parsee 
 * 4. Ajout de la comande de redirection
 * !! Creer une fct handle_error qui "free??" au peek + if (!new_redirs)
 */
int	parse_redirects(t_parser *parser, t_node *cmd_node)
{
	t_redir	redir;
	t_redir	*new_redirs;

	while (is_redirection(peek(parser)))
	{
		redir.type = parser->tokens[parser->pos].type;
		parser->pos++;
		if (parser->pos >= MAX_TOKENS || peek(parser) != WORD)
		{
			ft_printf("bash: syntax error near unexpected token `%s`\n",
				parser->tokens[parser->pos].value);
			parser->pos = MAX_TOKENS;
			return (0);
		}
		redir.filename = ft_strdup(parser->tokens[parser->pos].value);
		parser->pos++;
		new_redirs = ft_realloc(cmd_node->redirs,
				cmd_node->redir_count * sizeof(t_redir),
				(cmd_node->redir_count + 1) * sizeof(t_redir));
		if (!new_redirs)
		{
			free(redir.filename);
			parser->pos = MAX_TOKENS;
			return (0);
		}
		cmd_node->redirs = new_redirs;
		cmd_node->redirs[cmd_node->redir_count++] = redir;
	}
	return (1);
}

t_node	*parse_grouping(t_parser *parser)
{
	t_node	*subtree;

	if (peek(parser) == GROUPING_OPEN)
	{
		consume(parser);
		subtree = parse_semicolon(parser);
		if (peek(parser) != GROUPING_CLOSE)
		{
			ft_printf("Syntax error: unclosed grouping");
			return (NULL);
		}
		consume(parser);
		parse_redirects(parser, subtree);
		return (subtree);
	}
	else
		return (parse_command(parser));
}
