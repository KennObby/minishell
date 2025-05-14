/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:34:11 by oilyine-          #+#    #+#             */
/*   Updated: 2025/05/14 00:35:55 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_all_n_flag(const char *s)
{
	int	i;

	if (s[0] != '-')
		return (false);
	i = 1;
	while (s[1] == 'n')
		i++;
	return (s[i] == '\0');
}
