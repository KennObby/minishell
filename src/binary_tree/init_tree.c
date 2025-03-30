/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:40:00 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/30 11:55:26 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*create_leaf(char **args)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = CMD;
	node->args = args;
	node->writer = NULL;
	node->reader = NULL;
	node->redirs = NULL;
	node->redir_count = 0;
	return (node);
}

t_node	*create_node(t_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = type;
	node->args = NULL;
	node->writer = left;
	node->reader = right;
	node->redirs = NULL;
	node->redir_count = 0;
	return (node);
}
