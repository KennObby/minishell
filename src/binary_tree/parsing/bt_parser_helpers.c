/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_parser_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:07:55 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/26 23:12:45 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	*handle_syntax_error(t_parser *parser)
{
	print_syntax_error(parser);
	parser->pos = MAX_TOKENS;
	return (NULL);
}
