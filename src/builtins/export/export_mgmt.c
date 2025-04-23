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

int	builtin_export(t_node *cmd, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	char	*stripped;
	char	*eq;

	if (!cmd->args[1])
		return (print_export(*env));
	i = 1;
	while (cmd->args[i])
	{
		eq = ft_strchr(cmd->args[i], '=');
		if (eq)
		{
			key = ft_substr(cmd->args[i], 0, eq - cmd->args[i]);
			value = ft_strdup(eq + 1);
			if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
			{
				stripped = ft_substr(value, 1, ft_strlen(value) - 2);
				free(value);
				value = stripped;
			}
			update_or_add_env(env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}
