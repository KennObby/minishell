/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_mgmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 225/04/02 23:08:31 by oilyine-          #+#    #+#             */
/*   Updated: 225/04/02 23:30:27 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <unistd.h>

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

int	exec_builtin(t_data *d)
{
	char	*cmd;

	cmd = d->root->args[0];
	if (!ft_strcmp(cmd, "env"))
		return (d->exit_status = builtin_env(d->env_list));
	if (!ft_strcmp(cmd, "pwd"))
		return (d->exit_status = builtin_pwd());
	if (!ft_strcmp(cmd, "cd"))
		return (d->exit_status = builtin_cd(d));
	if (!ft_strcmp(cmd, "echo"))
		return (d->exit_status = builtin_echo(d->root, &d->env_list));
	if (!ft_strcmp(cmd, "export"))
		return (d->exit_status = builtin_export(d));
	if (!ft_strcmp(cmd, "unset"))
		return (d->exit_status = builtin_unset(d->root, &d->env_list));
	if (!ft_strcmp(cmd, "exit"))
		return (d->exit_status = builtin_exit(d));
	return (127);
}
