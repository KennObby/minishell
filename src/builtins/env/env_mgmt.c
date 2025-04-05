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

void	update_or_add_env(t_env **env, const char *key, const char *value)
{
	t_env	*curr;
	char	*combined;

	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	combined = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!combined)
		return ;
	ft_strcpy(combined, key);
	ft_strcat(combined, "=");
	ft_strcat(combined, value);
	*env = add_to_env_list(*env, combined);
	free(combined);
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

void	bump_shlvl(t_env *env)
{
	char	*lvl_str;
	char	*new_lvl_str;
	int		lvl;

	lvl_str = get_env_value(env, "SHLVL");
	lvl = 0;
	if (lvl_str)
		lvl = ft_atoi(lvl_str);
	lvl++;
	new_lvl_str = ft_itoa(lvl);
	if (!new_lvl_str)
		return ;
	update_or_add_env(&env, "SHLVL", new_lvl_str);
	free(new_lvl_str);
}
