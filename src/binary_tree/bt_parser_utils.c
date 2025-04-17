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

#include "../../inc/minishell.h"

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
	const char	*token_val;

	if (peek(parser) == END || !parser->tokens[parser->pos].value)
		token_val = "newline";
	else
		token_val = parser->tokens[parser->pos].value;
	ft_printf("bash: syntax error near unexpected token `%s'\n", token_val);
}

bool	expect_valid_token(t_parser *parser, t_type *expected, int count)
{
	t_type	current;
	int		i;

	current = peek(parser);
	i = 0;
	while (i < count)
	{
		if (current == expected[i])
			return (true);
		i++;
	}
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
