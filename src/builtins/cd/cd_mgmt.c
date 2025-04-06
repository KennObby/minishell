/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mgmt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:45:34 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/05 20:50:42 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdio.h>
#include <unistd.h>

char	*handle_cd_path(t_node *cmd, t_env **env)
{
	char	*path;
	int		count;

	count = 0;
	while (cmd->args[count])
		count++;
	if (count > 2)
	{
		ft_printf("cd: too many arguments\n");
		return (NULL);
	}
	if (count == 1)
	{
		path = get_env_value(*env, "HOME");
		if (!path)
		{
			ft_printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = get_env_value(*env, "OLDPWD");
		if (!path)
		{
			ft_printf("cd: OLDPWD not set\n");
			return (NULL);
		}
		ft_printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	return (path);
}

int	builtin_cd(t_node *cmd, t_env **env)
{
	char	*target;
	char	*old_pwd;
	char	cwd[MAX_PATH];

	target = handle_cd_path(cmd, env);
	if (!target)
		return (1);
	if (chdir(target) == -1)
	{
		ft_printf("cd: %s: ", target);
		perror("");
		return (1);
	}
	old_pwd = get_env_value(*env, "PWD");
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("cd: error retrieving current directory");
		return (1);
	}
	if (old_pwd)
		update_or_add_env(env, "OLDPWD", old_pwd);
	update_or_add_env(env, "PWD", cwd);
	return (0);
}
