/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:04:50 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/30 13:12:53 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*parse_semicolon(t_parser *parser)
{
	t_node	*left;
	t_node	*right;

	left = parse_logical(parser);
	if (peek(parser) == SEMICOLON)
	{
		consume(parser);
		right = parse_semicolon(parser);
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
	op = peek(parser);
	if (op == LOGICAL_AND || op == LOGICAL_OR)
	{
		consume(parser);
		right = parse_logical(parser);
		return (create_node(op, left, right));
	}
	return (left);
}

t_node	*parse_pipeline(t_parser *parser)
{
	t_node	*left;
	t_node	*right;

	left = parse_redirects(parser);
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
 * 2. Collecitng tokens until an operator is found
 * 3. Creating a leaf based on that node
 * 4. Attach redirections if any
 */
t_node	*parse_command(t_parser *parser)
{
	char	**args;
	int		arg_count;
	t_node	*cmd_node;

	args = malloc(MAX_ARGS * sizeof(char *));
	arg_count = 0;
	i = 0;
	while (parser->pos < MAX_TOKENS
		&& parser->tokens[parser->pos].type == CMD)
	{
		args[arg_count++] = ft_strdup(parser->tokens[parser->pos].value);
		parser->pos++;
	}
	args[arg_count] = NULL;
	cmd_node = create_leaf(args);
	parse_redirects(parser, cmd_node);
	return (cmd_node);
}

/* 1. Check si le token suivant est une redirection
 * 2. Assignation du type de redir
 * 3. Le filename devient la valeur du token parsee 
 * 4. Ajout de la comande de redirection
 * !! Creer une fct handle_error qui "free??" au peek + if (!new_redirs)
 */
t_node	*parse_redirects(t_parser *parser, t_node *cmd_node)
{
	t_redir	redir;
	t_redir	*new_redirs;

	node = parse_grouping(parser);
	while (is_redirection(peek(parser)))
	{
		redir.type = parser->tokens[parser->pos].type;
		parser->pos++;
		if (peek(parser) != WORD)
			ft_printf("Missing filename for redirection");
		redir.filename = ft_strdup(parser->tokens[parser->pos].value);
		parser->pos++;
		new_redirs = ft_realloc(cmd_node->redirs,
				cmd_node->redir_count * sizeof(t_redir),
				(cmd_node->redir_count + 1) * sizeof(t_redir));
		if (!new_redirs)
			ft_printf("Memory error");
		cmd_node->redirs = new_redirs;
		cmd_node->redirs[cmd_node->redir_count++] = redir;
	}
}
