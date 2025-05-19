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
	token.quoted = false;
	return (token);
}

int	tokenize_word(char *input, t_token *tokens, int i, int *pos)
{
	bool	in_quote;
	char	quote_char;
	char	*start;
	int		len;
	char	c;

	start = &input[*pos];
	quote_char = 0;
	in_quote = false;
	while (input[*pos])
	{
		c = input[*pos];
		if (!in_quote && (ft_isspace(c) || is_operator(c)))
			break ;
		if (c == '\'' || c == '"')
		{
			if (!in_quote)
			{
				in_quote = true;
				quote_char = c;
			}
			else if (c == quote_char)
				in_quote = false;
		}
		(*pos)++;
	}
	len = &input[*pos] - start;
	tokens[i] = create_token(WORD, ft_substr(start, 0, len));
	tokens[i].has_no_space_after = has_no_space_after(input, *pos);
	if ((start[0] == '\'' && start[len - 1] == '\'')
		|| (start[0] == '"' && start[len - 1] == '"'))
		tokens[i].quoted = true;
	printf("[TOKENIZER] Heredoc delimiter token: '%s' (quoted: %d)\n",
		tokens[i].value, tokens[i].quoted);
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
	tokens[i] = (t_token){END, NULL, false, false};
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
