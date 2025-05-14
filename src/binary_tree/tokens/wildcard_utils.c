/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:38:35 by oilyine-          #+#    #+#             */
/*   Updated: 2025/05/03 16:39:41 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	match_pattern(const char *str, const char *pattern)
{
	if (!str || !pattern)
		return (false);
	if (*pattern == '\0' && *str == '\0')
		return (true);
	if (*pattern == '*')
	{
		return (match_pattern(str, pattern + 1)
			|| (*str && match_pattern(str + 1, pattern)));
	}
	if (*pattern == *str)
		return (match_pattern(str + 1, pattern + 1));
	return (false);
}

void	restore_masked_wildcards(char **args)
{
	int				i;
	int				j;
	unsigned char	c;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			c = (unsigned char)args[i][j];
			if ((unsigned char)(~c) == '*')
				args[i][j] = (char)(~c);
			j++;
		}
		i++;
	}
}

void	restore_masked_wildcards_recursive(t_node *node)
{
	if (!node)
		return ;
	if (node->type == CMD && node->args)
		restore_masked_wildcards(node->args);
	restore_masked_wildcards_recursive(node->writer);
	restore_masked_wildcards_recursive(node->reader);
}

t_list	*build_list_from_args(char **args)
{
	t_list	*lst;
	int		i;

	lst = NULL;
	i = 0;
	while (args && args[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(args[i])));
		i++;
	}
	return (lst);
}

char	**list_to_args_array(t_list *list)
{
	size_t	size;
	char	**args;
	t_list	*tmp;
	int		i;

	size = ft_lstsize(list);
	if (size == 0)
	{
		args = malloc(sizeof(char *) * 1);
		if (!args)
			return (NULL);
		args[1] = NULL;
		return (args);
	}
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	tmp = list;
	i = 0;
	while (tmp)
	{
		args[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}
