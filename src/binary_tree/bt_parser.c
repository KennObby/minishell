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
		if (peek(parser) == SEMICOLON || peek(parser) == END)
		{
			print_syntax_error(parser);
			parser->pos = MAX_TOKENS;
			free_tree(left);
			return (NULL);
		}
		right = parse_semicolon(parser);
		if (!right)
		{
			free_tree(left);
			return (NULL);
		}
		return (create_node(SEMICOLON, left, right));
	}
	return (left);
}

t_node	*parse_logical(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_type	op;
	t_type	expected[2];

	expected[0] = WORD;
	expected[1] = GROUPING_OPEN;
	left = parse_pipeline(parser);
	while (peek(parser) == LOGICAL_AND || peek(parser) == LOGICAL_OR)
	{
		op = peek(parser);
		consume(parser);
		if (!expect_valid_token(parser, expected, 2))
		{
			free_tree(left);
			return (NULL);
		}
		right = parse_logical(parser);
		if (!right)
		{
			free_tree(left);
			return (NULL);
		}
		left = create_node(op, left, right);
	}
	return (left);
}

t_node	*parse_pipeline(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_type	expected[2];

	left = parse_grouping(parser);
	expected[0] = WORD;
	expected[1] = GROUPING_OPEN;
	if (peek(parser) == PIPE)
	{
		consume(parser);
		if (!expect_valid_token(parser, expected, 2))
		{
			free_tree(left);
			return (NULL);
		}
		right = parse_pipeline(parser);
		if (!right)
		{
			free_tree(left);
			return (NULL);
		}
		return (create_node(PIPE, left, right));
	}
	return (left);
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
			//print_syntax_error(parser);
			//parser->pos = MAX_TOKENS;
			prepare_heredocs(subtree);
			return (subtree);
		}
		consume(parser);
		parse_redirects(parser, subtree);
		return (subtree);
	}
	else
		return (parse_command(parser));
}

t_node	*parse(t_parser *parser)
{
	return (parse_semicolon(parser));
}
