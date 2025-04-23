/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:39:07 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/23 16:43:46 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	builtin_unset(t_node *cmd, t_env **env)
{
	int		i;
	t_env	*curr;
	t_env	*prev;

	i = 1;
	while (cmd->args[i])
	{
		prev = NULL;
		curr = *env;
		while (env)
		{
			if (ft_strcmp(curr->key, cmd->args[i]) == 0)
			{
				if (prev)
					prev->next = curr->next;
				else
					*env = curr->next;
				free(curr->key);
				free(curr->value);
				free(curr);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}
