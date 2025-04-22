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

/*
 * The function checks if there is no space after the token
 */
bool	has_no_space_after(const char *input, int pos)
{
	return (input[pos] && !ft_isspace(input[pos]));
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == ';'
		|| c == '(' || c == ')' || c == '|');
}

int	is_control_token(t_type type)
{
	return (type == LOGICAL_AND || type == LOGICAL_OR
		|| type == PIPE || type == SEMICOLON
		|| type == GROUPING_CLOSE || type == END);
}

/*
 * Checks if both tokens are WORD types and the following 
 * token has no spaces after it by keeping in memory the
 * end position of the previous token
 */
bool	should_merge(t_token prev, t_token next)
{
	return (prev.has_no_space_after && next.type == WORD);
}
