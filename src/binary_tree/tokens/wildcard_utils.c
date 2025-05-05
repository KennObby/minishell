/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:38:35 by oilyine-          #+#    #+#             */
/*   Updated: 2025/05/03 16:39:41 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	match_pattern(const char *str, const char *pattern)
{
	if (!str || !pattern)
		return (false);
	if (*pattern == '\0' && *str == '\0')
		return (true);
	if (*pattern == '*')
	{
		return (match_pattern(str, pattern + 1)
			|| (*str && match_pattern(str + 1, pattern)));
	}
	if (*pattern == *str)
		return (match_pattern(str + 1, pattern + 1));
	return (false);
}
