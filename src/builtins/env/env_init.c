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

t_env	*init_env_list(char **envp)
{
	int		i;
	t_env	*env_list;

	env_list = NULL;
	i = 0;
	while (envp[i])
		env_list = add_to_env_list(env_list, envp[i++]);
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
		arr[i++] = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
		ft_strcpy(arr[i], tmp->key);
		ft_strcat(arr[i], "=");
		ft_strcat(arr[i], tmp->value);
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}
