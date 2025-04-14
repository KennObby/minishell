/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:49:53 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/14 13:51:59 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdbool.h>

bool	has_no_space_after(char *input, int pos)
{
	while (input[pos] && ft_isspace(input[pos]))
		pos++;
	return (input[pos] && !is_operator(input[pos]));
}
