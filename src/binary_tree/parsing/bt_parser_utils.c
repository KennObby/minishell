/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:41:16 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/30 19:43:06 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdbool.h>

t_type	peek(t_parser *parser)
{
	if (parser->pos >= MAX_TOKENS)
		return (END);
	return (parser->tokens[parser->pos].type);
}

void	consume(t_parser *parser)
{
	parser->pos++;
}

int	is_redirection(t_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND || type == HEREDOC);
}

void	print_syntax_error(t_parser *parser)
{
	char	*token_val;

	if (peek(parser) == END || !parser->tokens[parser->pos].value)
		token_val = "newline";
	else
		token_val = parser->tokens[parser->pos].value;
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_val, 2);
	ft_putendl_fd("'", 2);
}

bool	expect_valid_token(t_parser *parser)
{
	if (peek(parser) == WORD || peek(parser) == GROUPING_OPEN)
		return (true);
	print_syntax_error(parser);
	parser->pos = MAX_TOKENS;
	return (false);
}

bool	expect_token_and_consume(t_parser *parser, t_type expected)
{
	if (peek(parser) != expected)
	{
		print_syntax_error(parser);
		parser->pos = MAX_TOKENS;
		return (false);
	}
	consume(parser);
	return (true);
}
