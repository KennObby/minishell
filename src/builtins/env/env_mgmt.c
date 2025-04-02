/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mgmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:52:36 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/02 19:04:42 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>

t_env	*add_to_env_list(t_env *list, char *env_line)
{
	t_env	*new;
	char	*eq;

	new = malloc(sizeof(t_env));
	eq = ft_strchr(env_line, '=');
	new->key = ft_substr(env_line, 0, eq - env_line);
	new->value = ft_strdup(eq + 1);
	new->next = list;
	return (new);
}

char	*resolve_path(char *cmd, t_env *env)
{
	char	*path;
	char	**paths;
	char	*full_path;
	char	*tmp_path;
	int		i;

	path = get_env_value(env, "PATH");
	paths = ft_split(path, ':');
	i = -1;
	while (paths && paths[++i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(full_path, X_OK) == 0)
		{
			free_str_array(paths);
			return (full_path);
		}
		free(full_path);
	}
	free_str_array(paths);
	return (NULL);
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
