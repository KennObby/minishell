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

int	builtin_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	builtin_echo(t_node *cmd, t_env **env)
{
	int		i;

	(void)env;
	i = 1;
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	return (0);
}

/*
 * A replacer par is_env, is_export etc ou trouver une
 * strat pour tout les builtins au fur et a mesure
 */
int	is_forkable_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "echo"));
}

int	is_parent_only_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "export"));
}

int	exec_builtin(t_node *cmd, t_env **env)
{
	if (!ft_strcmp(cmd->args[0], "env"))
		return (builtin_env(*env));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (builtin_cd(cmd, env));
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (builtin_echo(cmd, env));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (builtin_export(cmd, env));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (builtin_unset(cmd, env));
	ft_printf(">>> running builtin: %s\n", cmd->args[0]);
	return (127);
}
