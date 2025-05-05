/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_mgmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:58:06 by oilyine-          #+#    #+#             */
/*   Updated: 2025/05/03 17:08:34 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <dirent.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

t_list	*expand_wildcards(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*matches;
	struct stat		sb;

	dir = opendir(".");
	matches = NULL;
	if (!dir || !pattern)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if ((entry->d_name[0] == '.' && pattern[0] != '.'))
		{
			entry = readdir(dir);
			continue ;
		}
		if (stat(entry->d_name, &sb) != 0 || !(sb.st_mode & S_IFREG))
		{
			entry = readdir(dir);
			continue ;
		}
		if (!ft_strcmp(pattern, "*")
			|| (match_pattern(entry->d_name, pattern)))
		{
			if (ft_strlen(entry->d_name) < PATH_MAX)
				ft_lstadd_back(&matches, ft_lstnew(ft_strdup(entry->d_name)));
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

/*
 * The objective here is to:
 * 1. converting every args to a list with built_list
 * 2. Now that we have those, we can build a new char ** from that converted list
 *
 */
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
		args = malloc(sizeof(char *) * 2);
		args[0] = ft_strdup("");
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

void	process_single_argument(char *arg, t_list **new_args)
{
	t_list	*matches;
	t_list	*tmp;

	if (contains_wildcards(arg))
	{
		if (!arg)
			printf("DEBUG: arg is NULL before expand_wildcards\n");
		matches = expand_wildcards(arg);
		if (!matches)
			ft_lstadd_back(new_args, ft_lstnew(ft_strdup(arg)));
		else
		{
			tmp = matches;
			while (tmp)
			{
				ft_lstadd_back(new_args, ft_lstnew(ft_strdup(tmp->content)));
				tmp = tmp->next;
			}
			ft_lstclear(&matches, free);
		}
	}
	else
		ft_lstadd_back(new_args, ft_lstnew(ft_strdup(arg)));
}

void	expand_wildcards_node(t_node *node)
{
	t_list	*args_list;
	t_list	*new_args;
	t_list	*arg;
	int		i;

	args_list = build_list_from_args(node->args);
	new_args = NULL;
	arg = args_list;
	i = 0;
	while (arg)
	{
		if (i == 0)
			ft_lstadd_back(&new_args, ft_lstnew(ft_strdup(arg->content)));
		else
			process_single_argument(arg->content, &new_args);
		arg = arg->next;
		i++;
	}
	ft_lstclear(&args_list, free);
	free_args(node->args);
	node->args = list_to_args_array(new_args);
	ft_lstclear(&new_args, free);
}
