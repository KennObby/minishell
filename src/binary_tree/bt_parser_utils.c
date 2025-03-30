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

t_node	*parse(t_parser *parser)
{
	return (parse_semicolon(parser));
}
