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
	static const char	*redir_str[4];

	if (redir_str[0] == NULL)
	{
		redir_str[REDIRECT_IN] = "<";
		redir_str[REDIRECT_OUT] = ">";
		redir_str[APPEND] = ">>";
		redir_str[HEREDOC] = "<<";
	}
	if (type >= REDIRECT_IN && type <= HEREDOC)
		return (redir_str[type]);
	return ("UNKNOWN REDIR");
}

const char	*type_to_str(t_type type)
{
	static const char	*type_str[10];

	if (type_str[0] == NULL)
	{
		type_str[CMD] = "CMD";
		type_str[PIPE] = "|";
		type_str[SEMICOLON] = ";";
		type_str[LOGICAL_AND] = "&&";
		type_str[LOGICAL_OR] = "||";
		type_str[GROUPING] = "()";
		type_str[REDIRECT_IN] = ">";
		type_str[REDIRECT_OUT] = "<";
		type_str[APPEND] = ">>";
		type_str[HEREDOC] = "<<";
	}
	if (type >= CMD && type <= HEREDOC && type_str[type])
		return (type_str[type]);
	return ("UNKNOWN TYPE");
}
