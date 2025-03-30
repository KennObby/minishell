/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_str_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:48:19 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/30 20:05:45 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

const char	*redir_type_str(t_type type)
{
	switch (type)
	{
		case REDIRECT_IN:	return ("<");
		case REDIRECT_OUT: 	return (">");
		case APPEND:		return (">>");
		case HEREDOC:		return (">>");
		default:			return ("UNKNOWN REDIR");
	}
}

const char	*type_to_str(t_type type)
{
	switch (type)
	{
		case CMD:			return ("CMD");
		case PIPE:			return ("|");
		case SEMICOLON:		return (";");
		case LOGICAL_AND:	return ("&&");
		case LOGICAL_OR:	return ("||");
		case GROUPING:		return ("()");
		case REDIRECT_IN:
		case REDIRECT_OUT:
		case APPEND:
		case HEREDOC:		return redir_type_str(type);
		default:			return ("UNKNOWN");
	}
}
