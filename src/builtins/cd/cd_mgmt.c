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

char	*handle_cd_path(t_data *d)
{
	char	*path;
	int		count;
	char	*home;
	char	*suffix;
	char	*expanded;

	count = 0;
	while (d->root->args[count])
		count++;
	if (count > 2)
	{
		ft_putendl_fd("bash: cd : too many arguments", 2);
		g_data->exit_status = 1;
		return (NULL);
	}
	if (count == 1)
	{
		path = get_env_value(d->env_list, "HOME");
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			g_data->exit_status = 1;
			return (NULL);
		}
		return (ft_strdup(path));
	}
	if (ft_strcmp(d->root->args[1], "-") == 0)
	{
		path = get_env_value(d->env_list, "OLDPWD");
		if (!path)
		{
			ft_printf("cd: OLDPWD not set\n");
			g_data->exit_status = 1;
			return (NULL);
		}
		ft_printf("%s\n", path);
		return (ft_strdup(path));
	}
	if (d->root->args[1][0] == '~')
	{
		home = get_env_value(d->env_list, "HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			g_data->exit_status = 1;
			return (NULL);
		}
		suffix = d->root->args[1] + 1;
		expanded = ft_strjoin(home, suffix);
		return (expanded);
	}
	if ((ft_strcmp(d->root->args[1], "--") == 0))
	{
		home = get_env_value(d->env_list, "HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set");
			g_data->exit_status = 1;
			return (NULL);
		}
		return (ft_strdup(home));
	}
	return (ft_strdup(d->root->args[1]));
}

int	builtin_cd(t_data *d)
{
	char	*target;
	char	*old_pwd;
	char	cwd[MAX_PATH];

	target = handle_cd_path(d);
	if (!target)
		return (g_data->exit_status = 1);
	if (chdir(target) == -1)
	{
		ft_putendl_fd("No such file or directory", 2);
		free(target);
		return (g_data->exit_status = 1);
	}
	old_pwd = get_env_value(d->env_list, "PWD");
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd("cd: error retrieving current directory", 2);
		free(target);
		return (g_data->exit_status = 1);
	}
	if (old_pwd)
		update_or_add_env(&d->env_list, "OLDPWD", old_pwd);
	update_or_add_env(&d->env_list, "PWD", cwd);
	free(target);
	return (g_data->exit_status = 0);
}
