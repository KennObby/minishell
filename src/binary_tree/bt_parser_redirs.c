/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_parser_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:39:22 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/16 17:51:05 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	add_redirect(t_parser *parser, t_node *cmd_node, t_redir redir)
{
	t_redir	*new_redirs;

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
	return (1);
}

int	parse_redirects(t_parser *parser, t_node *cmd_node)
{
	t_redir		redir;

	while (is_redirection(peek(parser)))
	{
		redir.type = parser->tokens[parser->pos].type;
		parser->pos++;
		if (parser->pos >= MAX_TOKENS)
		{
			print_syntax_error(parser);
			return (0);
		}
		if (peek(parser) != WORD)
		{
			print_syntax_error(parser);
			parser->pos = MAX_TOKENS;
			return (0);
		}
		redir.filename = ft_strdup(parser->tokens[parser->pos].value);
		parser->pos++;
		if (!add_redirect(parser, cmd_node, redir))
			return (0);
	}
	return (1);
}
