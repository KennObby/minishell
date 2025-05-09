/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:46:50 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/02 18:52:11 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>

t_env	*init_env_list(char **envp)
{
	int		i;
	t_env	*env_list;

	env_list = NULL;
	i = 0;
	while (envp[i])
		env_list = add_env_from_line(env_list, envp[i++]);
	return (env_list);
}

char	**env_list_to_array(t_env *env)
{
	int		len;
	int		i;
	char	**arr;
	t_env	*tmp;

	len = 0;
	i = 0;
	tmp = env;
	while (tmp && ++len)
		tmp = tmp->next;
	arr = malloc(sizeof(char *) * (len + 1));
	tmp = env;
	while (tmp)
	{
		arr[i] = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
		ft_strcpy(arr[i], tmp->key);
		ft_strcat(arr[i], "=");
		ft_strcat(arr[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

t_env	*copy_env(t_env *env)
{
	t_env	*copy;
	t_env	*tail;
	t_env	*new;

	copy = NULL;
	tail = NULL;
	while (env)
	{
		new = malloc(sizeof(t_env));
		new->key = ft_strdup(env->key);
		if (env->value)
			new->value = ft_strdup(env->value);
		else
			new->value = NULL;
		new->next = NULL;
		if (!copy)
			copy = new;
		else
			tail->next = new;
		tail = new;
		env = env->next;
	}
	return (copy);
}

void	ensure_minimal_env(t_env **env)
{
	char	cwd[MAX_PATH];

	if (!get_env_value(*env, "PATH"))
		update_or_add_env(env, "PATH", "/usr/bin:/bin");
	if (!get_env_value(*env, "PWD"))
	{
		if (getcwd(cwd, sizeof(cwd)))
			update_or_add_env(env, "PWD", cwd);
	}
	if (!get_env_value(*env, "SHLVL"))
		update_or_add_env(env, "SHLVL", "1");
}

void	sort_env(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char	*tmp_key;
	char	*tmp_val;

	i = env;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
			{
				tmp_key = i->key;
				i->key = j->key;
				j->key = tmp_key;
				tmp_val = i->value;
				i->value = j->value;
				j->value = tmp_val;
			}
			j = j->next;
		}
		i = i->next;
	}
}
