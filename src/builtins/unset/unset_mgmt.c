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
#include <stdbool.h>

bool	is_valid_unset_identifier(const char *s)
{
	ft_printf("DEBUG validating: ›%s‹ → first char = '%c' (code %d)\n",
		s, *s, (unsigned char)*s);
	if (!s || !(ft_isalpha((unsigned char)*s) || *s == '_'))
		return (false);
	s++;
	while (*s)
	{
		if (!(ft_isalnum((unsigned char)*s) || *s == '_'))
			return (false);
		s++;
	}
	return (true);
}

int	builtin_unset(t_node *cmd, t_env **env)
{
	int		i;
	int		had_error;
	t_env	*curr;
	t_env	*prev;
	char	*key;

	i = 1;
	had_error = 0;
	while (cmd->args[i])
	{
		key = cmd->args[i++];
		if (!is_valid_unset_identifier(key))
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(key, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			had_error = 1;
			continue ;
		}
		prev = NULL;
		curr = *env;
		while (curr && ft_strcmp(curr->key, key) != 0)
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
		}
	}
	if (had_error)
		return (1);
	else
		return (0);
}
