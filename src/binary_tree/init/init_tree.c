/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembo    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:40:00 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/26 17:38:29 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_node	*create_leaf(char **args)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		perror("minishell: malloc on leaf failed");
		exit(1);
	}
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
	if (!node)
	{
		perror("minishell: malloc on node failed");
		exit(1);
	}
	node->type = type;
	node->args = NULL;
	node->writer = left;
	node->reader = right;
	node->redirs = NULL;
	node->redir_count = 0;
	printf("[NODE CREATED] Created node of type: %d\n" "at %p\n", type, node);
	return (node);
}
