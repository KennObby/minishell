/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:15:16 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/23 16:38:47 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdbool.h>
#include <stdlib.h>

int	print_export(t_env *env)
{
	t_env	*sorted;
	t_env	*tmp;

	sorted = copy_env(env);
	tmp = sorted;
	sort_env(sorted);
	while (tmp)
	{
		if (tmp->value)
			ft_printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		else
			ft_printf("export %s\n", tmp->key);
		tmp = tmp->next;
	}
	free_env_list(sorted);
	return (0);
}

bool	is_valid_identifier(const char *s)
{
	if (!s || (!ft_isalpha(*s) && *s != '_'))
		return (false);
	s++;
	while (*s)
	{
		if (*s == '=')
			break ;
		if (!ft_isalnum(*s) && *s != '_')
			return (false);
		s++;
	}
	return (true);
}

int	builtin_export(t_data *d)
{
	int		i;
	char	*key;
	char	*value;
	char	*eq;

	if (!d->root->args[1])
		return (print_export(d->env_list));
	d->exit_status = 0;
	i = 1;
	while (d->root->args[i])
	{
		eq = ft_strchr(d->root->args[i], '=');
		if (eq)
		{
			key = ft_substr(d->root->args[i], 0, eq - d->root->args[i]);
			value = ft_strdup(eq + 1);
		}
		else
		{
			key = ft_strdup(d->root->args[i]);
			value = ft_strdup("");
		}
		if (!is_valid_identifier(key))
		{
			ft_putendl_fd("not a valid identifier", 2);
			d->exit_status = 1;
		}
		else
			update_or_add_env(&d->env_list, key, value);
		free(key);
		free(value);
		i++;
	}
	return (d->exit_status);
}
