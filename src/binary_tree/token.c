/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 10:58:34 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/30 11:39:49 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == ';'
		|| c == '&' || c == '(' || c == ')' || c == '|');
}

/*
 * Tokenizer based on struct t_type. 
 * 
 */
t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	int		j;
	int		pos;
	int		start;

	tokens = malloc(MAX_TOKENS * sizeof(t_token));
	i = 0;
	pos = 0;
	while (input[pos])
	{
		if (ft_isspace(input[pos]))
		{
			pos++;
			continue ;
		}
		start = pos;
		if (ft_strncmp(&input[pos], ">>", 2) == 0)
		{
			tokens[i++] = (t_token){APPEND, ft_strdup(">>")};
			pos += 2;
		}
		else if (ft_strncmp(&input[pos], "<<", 2) == 0)
		{
			tokens[i++] = (t_token){HEREDOC, ft_strdup("<<")};
			pos += 2;
		}
		else if (ft_strncmp(&input[pos], "&&", 2) == 0)
		{
			tokens[i++] = (t_token){LOGICAL_AND, ft_strdup("&&")};
			pos += 2;
		}
		else if (ft_strncmp(&input[pos], "||", 2) == 0)
		{
			tokens[i++] = (t_token){LOGICAL_OR, ft_strdup("||")};
			pos += 2;
		}
		else if (input[pos] == '>')
		{
			tokens[i++] = (t_token){REDIRECT_OUT, ft_strdup(">")};
			pos++;
		}
		else if (input[pos] == '<')
		{
			tokens[i++] = (t_token){REDIRECT_IN, ft_strdup("<")};
			pos++;
		}
		else if (input[pos] == '|')
		{
			tokens[i++] = (t_token){PIPE, ft_strdup("|")};
			pos++;
		}
		else if (input[pos] == ';')
		{
			tokens[i++] = (t_token){SEMICOLON, ft_strdup("")};
			pos++;
		}
		else if (input[pos] == '(')
		{
			tokens[i++] = (t_token){GROUPING_OPEN, ft_strdup("(")};
			pos++;
		}
		else if (input[pos] == ')')
		{
			tokens[i++] = (t_token){GROUPING_CLOSE, ft_strdup(")")};
			pos++;
		}
		else
		{
			while (input[pos] && !ft_isspace(input[pos])
				&& !is_operator(input[pos]))
				pos++;
			j = pos;
			while (input[j] && ft_isspace(intput[j]))
				j++;
			tokens[i++] = (t_token){WORD, ft_substr(input, start, pos - start)};
		}
	}
	tokens[i] = (t_token){END, NULL};
	return (tokens);
}
