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

t_node	*parse_semicolon(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_node	*new_node;

	left = parse_logical_or(parser);
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
		new_node = create_node(SEMICOLON, left, right);
		if (!new_node)
			return (free_tree(left), free_tree(right), NULL);
		left = new_node;
	}
	return (left);
}

t_node	*parse_logical_or(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_node	*new_node;

	left = parse_logical_and(parser);
	if (!left)
		return (NULL);
	while (peek(parser) == LOGICAL_OR)
	{
		consume(parser);
		if (!expect_valid_token(parser))
			return (free_tree(left), left = NULL, NULL);
		right = parse_logical_and(parser);
		if (!right)
			return (free_tree(left), left = NULL, NULL);
		new_node = create_node(LOGICAL_OR, left, right);
		if (!new_node)
			return (free_tree(left), free_tree(right), NULL);
		left = new_node;
	}
	return (left);
}

t_node	*parse_logical_and(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_node	*new_node;

	left = parse_pipeline(parser);
	if (!left)
		return (NULL);
	while (peek(parser) == LOGICAL_AND)
	{
		consume(parser);
		if (!expect_valid_token(parser))
			return (free_tree(left), left = NULL, NULL);
		right = parse_pipeline(parser);
		if (!right)
			return (free_tree(left), left = NULL, NULL);
		new_node = create_node(LOGICAL_AND, left, right);
		if (!new_node)
			return (free_tree(left), free_tree(right), NULL);
		left = new_node;
	}
	return (left);
}

t_node	*parse_pipeline(t_parser *parser)
{
	t_node	*left;
	t_node	*right;
	t_node	*new_node;
	t_type	op;

	left = parse_grouping(parser);
	while (peek(parser) == PIPE)
	{
		op = peek(parser);
		consume(parser);
		if (!expect_valid_token(parser))
			return (free_tree(left), left = NULL, NULL);
		right = parse_pipeline(parser);
		if (!right)
			return (free_tree(left), free_tree(right), NULL);
		new_node = create_node(op, left, right);
		if (!new_node)
			return (free_tree(left), free_tree(right), NULL);
		left = new_node;
	}
	return (left);
}

t_node	*parse_grouping(t_parser *parser)
{
	t_node	*subtree;
	t_node	*wrapper;

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
		wrapper = create_node(SUBSHELL, subtree, NULL);
		if (!wrapper)
			return (free_tree(subtree), NULL);
		if (!parse_redirects(parser, &wrapper))
			return (free_tree(wrapper), NULL);
		return (wrapper);
	}
	else
		return (parse_command(parser));
}

t_node	*parse(t_parser *parser)
{
	return (parse_semicolon(parser));
}
