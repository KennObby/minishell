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

#include "../../../inc/minishell.h"
#include <stdbool.h>

t_token	create_token(t_type type, char *val)
{
	t_token	token;

	token.type = type;
	token.value = val;
	token.has_no_space_after = false;
	return (token);
}

int	tokenize_word(char *input, t_token *tokens, int i, int *pos)
{
	int		start;
	char	*value;
	char	quote;

	start = *pos;
	if (input[*pos] == '\'' || input[*pos] == '"')
	{
		quote = input[(*pos)++];
		while (input[*pos] && input[*pos] != quote)
			(*pos)++;
		if (input[*pos] == quote)
			(*pos)++;
	}
	else
	{
		while (input[*pos] && !ft_isspace(input[*pos])
			&& !is_operator(input[*pos]))
		{
			if (input[*pos] == '=' && (input[*pos + 1] == '"'
					|| input[*pos + 1] == '\''))
			{
				(*pos)++;
				quote = input[(*pos)++];
				while (input[*pos] && input[*pos] != quote)
					(*pos)++;
				if (input[*pos] == quote)
					(*pos)++;
				break ;
			}
			(*pos)++;
		}
	}
	value = ft_substr(input, start, *pos - start);
	tokens[i] = create_token(WORD, value);
	tokens[i].has_no_space_after = has_no_space_after(input, *pos);
	return (i + 1);
}
/*
 * Tokenizer based on struct t_type. 
 * 
 */
t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	int		pos;

	tokens = ft_calloc(MAX_TOKENS, sizeof(t_token));
	i = 0;
	pos = 0;
	while (input[pos] && i < MAX_TOKENS - 1)
	{
		if (ft_isspace(input[pos]))
		{
			pos++;
			continue ;
		}
		else if (input[pos] == '&' && input[pos + 1] == '&')
		{
			tokens[i++] = create_token(LOGICAL_AND, ft_strdup("&&"));
			pos += 2;
		}
		else if (ft_strncmp(&input[pos], "||", 2) == 0)
		{
			tokens[i++] = create_token(LOGICAL_OR, ft_strdup("||"));
			pos += 2;
		}
		else if (is_operator(input[pos]))
			i = tokenize_operators(input, tokens, i, &pos);
		else
			i = tokenize_word(input, tokens, i, &pos);
	}
	tokens[i] = (t_token){END, NULL, false};
	tokens[i + 1] = (t_token){0};
	return (tokens);
}

int	tokenize_operators(char *input, t_token *tokens, int i, int *pos)
{
	if (ft_strncmp(&input[*pos], ">>", 2) == 0)
	{
		tokens[i++] = create_token(APPEND, ft_strdup(">>"));
		*pos += 2;
	}
	else if (ft_strncmp(&input[*pos], "<<", 2) == 0)
	{
		tokens[i++] = create_token(HEREDOC, ft_strdup("<<"));
		*pos += 2;
	}
	else if (input[*pos] == '&' && input[*pos + 1] == '&')
	{
		tokens[i++] = create_token(LOGICAL_AND, ft_strdup("&&"));
		*pos += 2;
	}
	else if (ft_strncmp(&input[*pos], "||", 2) == 0)
	{
		tokens[i++] = create_token(LOGICAL_OR, ft_strdup("||"));
		*pos += 2;
	}
	else if (input[*pos] == '>')
	{
		tokens[i++] = create_token(REDIRECT_OUT, ft_strdup(">"));
		(*pos)++;
	}
	else if (input[*pos] == '<')
	{
		tokens[i++] = create_token(REDIRECT_IN, ft_strdup("<"));
		(*pos)++;
	}
	else if (input[*pos] == '|')
	{
		tokens[i++] = create_token(PIPE, ft_strdup("|"));
		(*pos)++;
	}
	else if (input[*pos] == ';')
	{
		tokens[i++] = create_token(SEMICOLON, ft_strdup(";"));
		(*pos)++;
	}
	else if (input[*pos] == '(')
	{
		tokens[i++] = create_token(GROUPING_OPEN, ft_strdup("("));
		(*pos)++;
	}
	else if (input[*pos] == ')')
	{
		tokens[i++] = create_token(GROUPING_CLOSE, ft_strdup(")"));
		(*pos)++;
	}
	else
		return (i);
	return (i);
}
