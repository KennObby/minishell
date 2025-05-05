/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:39:48 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/30 18:47:30 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <string.h>

void	free_tree(t_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	free_tree(node->writer);
	free_tree(node->reader);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	if (node->redirs)
	{
		i = 0;
		while (i < node->redir_count)
			free(node->redirs[i++].filename);
		free(node->redirs);
	}
	node->args = NULL;
	node->redirs = NULL;
	node->writer = NULL;
	node->reader = NULL;
	free(node);
}

void	free_tokens(t_token	*tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != END)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
