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
	if (!args)
		return (NULL);
	arg_count = 0;
	while (parser->pos < MAX_TOKENS
		&& parser->tokens[parser->pos].type == WORD)
	{
		args[arg_count++] = ft_strdup(parser->tokens[parser->pos].value);
		parser->pos++;
	}
	args[arg_count] = NULL;
	if (arg_count == 0 && !is_redirection(peek(parser)))
	{
		free(args);
		ft_printf("minishell: invalid command");
		return (NULL);
	}
	cmd_node = create_leaf(args);
	if (!cmd_node)
		return (NULL);
	parse_redirects(parser, cmd_node);
	return (cmd_node);
}

/* 1. Check si le token suivant est une redirection
 * 2. Assignation du type de redir
 * 3. Le filename devient la valeur du token parsee 
 * 4. Ajout de la comande de redirection
 * !! Creer une fct handle_error qui "free??" au peek + if (!new_redirs)
 */
void	parse_redirects(t_parser *parser, t_node *cmd_node)
{
	t_redir	redir;
	t_redir	*new_redirs;

	while (is_redirection(peek(parser)))
	{
		redir.type = parser->tokens[parser->pos].type;
		parser->pos++;
		if (parser->pos >= MAX_TOKENS || peek(parser) != WORD)
		{
			free_tree(cmd_node);
			ft_printf("Missing filename for redirection");
			parser->pos = MAX_TOKENS;
			return ;
		}
		redir.filename = ft_strdup(parser->tokens[parser->pos].value);
		parser->pos++;
		new_redirs = ft_realloc(cmd_node->redirs,
				cmd_node->redir_count * sizeof(t_redir),
				(cmd_node->redir_count + 1) * sizeof(t_redir));
		if (!new_redirs)
		{
			free_tree(cmd_node);
			exit(1);
		}
		cmd_node->redirs = new_redirs;
		cmd_node->redirs[cmd_node->redir_count++] = redir;
	}
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
			parser->pos = MAX_TOKENS;
			return (NULL);
		}
		consume(parser);
		parse_redirects(parser, subtree);
		return (subtree);
	}
	else
		return (parse_command(parser));
}
