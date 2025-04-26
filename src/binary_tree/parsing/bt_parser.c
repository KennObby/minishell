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

#include "../../../inc/minishell.h"
#include <stdlib.h>
#include <string.h>

t_node	*parse_semicolon(t_parser *parser)
{
	t_node	*left;
	t_node	*right;

	left = parse_logical(parser);
	if (!left)
		return (NULL);
	while (peek(parser) == SEMICOLON)
	{
		consume(parser);
		if (!expect_valid_token(parser))
			return (free_tree(left), left = NULL, NULL);
		right = parse_semicolon(parser);
		if (!right)
			return (free_tree(left), left = NULL, NULL);
		left = create_node(SEMICOLON, left, right);
	}
	return (left);
}

t_node	*parse_logical(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_type	op;

	left = parse_pipeline(parser);
	if (!left)
		return (NULL);
	while (peek(parser) == LOGICAL_AND || peek(parser) == LOGICAL_OR)
	{
		op = peek(parser);
		consume(parser);
		if (!expect_valid_token(parser))
			return (free_tree(left), left = NULL, NULL);
		right = parse_logical(parser);
		if (!right)
			return (free_tree(left), left = NULL, NULL);
		left = create_node(op, left, right);
	}
	return (left);
}

t_node	*parse_pipeline(t_parser *parser)
{
	t_node	*left;
	t_node	*right;

	left = parse_grouping(parser);
	while (peek(parser) == PIPE)
	{
		consume(parser);
		if (!expect_valid_token(parser))
			return (free_tree(left), left = NULL, NULL);
		right = parse_pipeline(parser);
		if (!right)
			return (free_tree(left), left = NULL, NULL);
		left = create_node(PIPE, left, right);
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
		if (!subtree)
		{
			parser->pos = MAX_TOKENS;
			return (NULL);
		}
		if (peek(parser) != GROUPING_CLOSE)
		{
			print_syntax_error(parser);
			free_tree(subtree);
			parser->pos = MAX_TOKENS;
			return (NULL);
		}
		consume(parser);
		if (!parse_redirects(parser, subtree))
			return (free_tree(subtree), NULL);
		return (subtree);
	}
	else
		return (parse_command(parser));
}

t_node	*parse(t_parser *parser)
{
	return (parse_semicolon(parser));
}
