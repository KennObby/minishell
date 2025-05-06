/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_parser_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:23:25 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/22 11:28:47 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdlib.h>

void	expand_node_args(t_node *node, t_env *env, int *status)
{
	int		i;
	char	*exp;

	if (!node)
		return ;
	if (node->writer)
		expand_node_args(node->writer, env, status);
	if (node->reader)
		expand_node_args(node->reader, env, status);
	i = 0;
	if (node->type == CMD && node->args)
	{
		while (i < node->redir_count)
		{
			exp = expand_argument(node->redirs[i].filename,
					&env);
			free(node->args[i]);
			node->redirs[i].filename = exp;
			i++;
		}
		i = 0;
		while (node->args[i])
		{
			exp = expand_argument(node->args[i], &env);
			free(node->args[i]);
			node->args[i] = exp;
			i++;
		}
	}
}
