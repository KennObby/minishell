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

void	expand_node_args(t_node *node, t_env *env)
{
	int		i;
	char	*expanded;

	if (!node || node->type != CMD || !node->args)
		return ;
	expand_node_args(node->reader, env);
	expand_node_args(node->writer, env);
	i = 0;
	while (node->args && node->args[i])
	{
		expanded = NULL;
		if (node->args[i][0] == '\'' && ft_strlen(node->args[i]) >= 2)
			expanded = handle_single_quotes(node->args[i]);
		else if (node->args[i][0] == '"' && ft_strlen(node->args[i]) >= 2)
			expanded = handle_double_quotes(node->args[i], &env);
		else if (ft_strchr(node->args[i], '$') && ft_strlen(node->args[i]) >= 2)
			expanded = expand_double_quoted(ft_strdup(node->args[i]), &env);
		if (expanded)
		{
			free(node->args[i]);
			node->args[i] = expanded;
		}
		i++;
	}
}
