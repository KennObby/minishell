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

#include "../../../inc/minishell.h"
#include <stdlib.h>

int	redir_is_quoted(t_redir *redir)
{
	return (redir && redir->is_quoted);
}

int	add_redirect(t_parser *parser, t_node *cmd_node, t_redir redir)
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

int	parse_redirects(t_parser *parser, t_node **cmd_node)
{
	t_redir		redir;
	char		*expanded;

	ft_bzero(&redir, sizeof(t_redir));
	while (is_redirection(peek(parser)))
	{
		if (!(*cmd_node))
		{
			*cmd_node = create_empty_node();
			if (!*cmd_node)
				return (0);
		}
		redir.type = parser->tokens[parser->pos].type;
		parser->pos++;
		if (parser->pos >= MAX_TOKENS || peek(parser) != WORD)
		{
			print_syntax_error(parser);
			parser->pos = MAX_TOKENS;
			return (0);
		}
		printf("[PARSER] Raw heredoc delimiter: '%s' (quoted: %d)\n",
			parser->tokens[parser->pos].value, parser->tokens[parser->pos].quoted);
		redir.filename = ft_strdup(parser->tokens[parser->pos].value);
		redir.fd = -1;
		redir.is_quoted = parser->tokens[parser->pos].quoted;
		parser->pos++;
		expanded = expand_argument(redir.filename, &g_data->env_list);
		printf("[PARSER] Expanded heredoc delimiter: '%s'\n", expanded);
		free(redir.filename);
		redir.filename = expanded;
		if (!add_redirect(parser, *cmd_node, redir))
			return (free(redir.filename), 0);
	}
	return (1);
}
