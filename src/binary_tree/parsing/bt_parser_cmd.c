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

#include "../../../inc/minishell.h"
#include <stdlib.h>
#include <string.h>

int	parse_single_redirect(t_parser *parser, t_node *cmd_node)
{
	t_type	redir_type;
	char	*redir_filename;
	t_redir	redir;

	redir_type = parser->tokens[parser->pos].type;
	parser->pos++;
	if (peek(parser) != WORD)
		return (handle_syntax_error(parser), 0);
	redir_filename = ft_strdup(parser->tokens[parser->pos].value);
	if (!redir_filename)
		return (handle_syntax_error(parser), 0);
	parser->pos++;
	redir.type = redir_type;
	redir.filename = redir_filename;
	redir.fd = -1;
	if (!add_redirect(parser, cmd_node, redir))
	{
		free(redir_filename);
		return (handle_syntax_error(parser), 0);
	}
	return (1);
}

char	*merge_tokens(t_parser *parser)
{
	char	*merged;
	char	*tmp;

	merged = ft_strdup(parser->tokens[parser->pos].value);
	if (!merged)
		return (NULL);
	parser->pos++;
	while (parser->pos < MAX_TOKENS
		&& should_merge(parser->tokens[parser->pos - 1],
			parser->tokens[parser->pos]))
	{
		tmp = merged;
		merged = ft_strjoin(merged, parser->tokens[parser->pos].value);
		free(tmp);
		if (!merged)
			return (NULL);
		parser->pos++;
	}
	return (merged);
}

char	**collect_args(t_parser *parser, t_node *cmd_node, int *arg_count)
{
	char	**args;
	char	**new_args;
	char	*arg;
	int		n;

	args = NULL;
	*arg_count = 0;
	while (parser->pos < MAX_TOKENS && peek(parser) != END)
	{
		if (is_control_token(peek(parser)))
			break ;
		if (is_redirection(peek(parser)))
		{
			if (!parse_single_redirect(parser, cmd_node))
				return ((free_args(args, n)), NULL);
			continue ;
		}
		arg = merge_tokens(parser);
		if (!arg)
			return (free_args(args, n), NULL);
		new_args = ft_realloc(args, n * sizeof(*args),
				(n + 1) * sizeof(*args));
		if (!new_args)
			return (free(arg), free_args(args, *arg_count), NULL);
		args = new_args;
		args[n++] = arg;
	}
	*arg_count = n;
	return (args);
}

int	finalize_args(t_node *cmd, char **args, int arg_count)
{
	char	**new_args;

	if (!args && cmd->redir_count == 0)
	{
		free_tree(cmd);
		return (0);
	}
	new_args = ft_realloc(args, arg_count * sizeof(char *),
			(arg_count + 1) * sizeof(char *));
	if (!new_args)
	{
		free_tree(cmd);
		return (0);
	}
	new_args[arg_count] = NULL;
	cmd->args = new_args;
	return (1);
}

t_node	*parse_command(t_parser *parser)
{
	char	**args;
	int		arg_count;
	t_node	*cmd_node;

	if (peek(parser) != WORD && !is_redirection(peek(parser)))
		return (handle_syntax_error(parser));
	cmd_node = create_leaf(NULL);
	if (!cmd_node)
		return (NULL);
	args = collect_args(parser, cmd_node, &arg_count);
	if (!finalize_args(cmd_node, args, arg_count))
		return (NULL);
	if (arg_count == 0 && cmd_node->redir_count == 0)
	{
		free_tree(cmd_node);
		return (handle_syntax_error(parser));
	}
	return (cmd_node);
}
