/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_parser_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:43:10 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/16 18:14:26 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**collect_args(t_parser *parser, int *arg_count)
{
	char	**args;
	char	*merged;
	char	*tmp;
	char	**new_args;

	args = NULL;
	*arg_count = 0;
	while (parser->pos < MAX_TOKENS
		&& parser->tokens[parser->pos].type == WORD
		&& !is_control_token(parser->tokens[parser->pos].type))
	{
		merged = ft_strdup(parser->tokens[parser->pos++].value);
		if (!merged)
			return (free_args(args, *arg_count), NULL);
		while (parser->pos < MAX_TOKENS
			&& should_merge(parser->tokens[parser->pos - 1],
				parser->tokens[parser->pos]))
		{
			tmp = merged;
			merged = ft_strjoin(merged, parser->tokens[parser->pos++].value);
			if (!merged)
				return (free_args(args, *arg_count), NULL);
			free(tmp);
		}
		new_args = ft_realloc(args, *arg_count * sizeof(char *),
				(*arg_count + 1) * sizeof(char *));
		if (!new_args)
			return (free(merged), free_args(args, *arg_count), NULL);
		args = new_args;
		args[(*arg_count)++] = merged;
	}
	return (args);
}

t_node	*parse_command(t_parser *parser)
{
	char	**args;
	int		arg_count;
	t_node	*cmd_node;

	args = collect_args(parser, &arg_count);
	if (!args && !is_redirection(peek(parser)))
		return (NULL);
	args = ft_realloc(args, arg_count * sizeof(char *),
			(arg_count + 1) * sizeof(char *));
	if (!args)
		return (free_args(args, arg_count), NULL);
	args[arg_count] = NULL;
	cmd_node = create_leaf(args);
	if (!cmd_node)
		return (NULL);
	if (!parse_redirects(parser, cmd_node))
		return (free_tree(cmd_node), NULL);
	if (arg_count == 0 && cmd_node->redir_count == 0)
	{
		print_syntax_error(parser);
		parser->pos = MAX_TOKENS;
		free_tree(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}
