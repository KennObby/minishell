/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_mgmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 23:08:31 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/02 23:30:27 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

/*
 * A replacer par is_env, is_export etc ou trouver une
 * strat pour tout les builtins au fur et a mesure
 */
int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "env"));
}

void	exec_builtin(t_node *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->args[0], "env"))
		builtin_env(env);
}
