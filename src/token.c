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

#include "../inc/minishell.h"

/*
 * Tokenizer based on struct t_type. 
 * Calling my own ft_strtok in Libft by detecting 
 */
t_token	*tokenize(char *input)
{
	t_token	*tokens;
	char	*token_str;
	int		i;

	tokens = malloc(MAX_TOKENS * sizeof(t_token));
	token_str = ft_strtok(input, " ");
	i = 0;
	while (token_str != NULL)
	{
		tokens[i].value = token_str;
		if (ft_strcmp(token_str, "|") == 0)
			tokens[i].type = PIPE;
		else if (ft_strcmp(token_str, ";") == 0)
			tokens[i].type = SEMICOLON;
		else if (ft_strcmp(token_str, "&&") == 0)
			tokens[i].type = LOGICAL_AND;
		else if (ft_strcmp(token_str, "||") == 0)
			tokens[i].type = LOGICAL_OR;
		else if (ft_strcmp(token_str, "<") == 0)
			tokens[i].type = REDIRECT_IN;
		else if (ft_strcmp(token_str, ">") == 0)
			tokens[i].type = REDIRECT_OUT;
		else if (ft_strcmp(token_str, "<<") == 0)
			tokens[i].type = APPEND;
		else if (ft_strcmp(token_str, ">>") == 0)
			tokens[i].type = HEREDOC;
		else
			tokens[i].type = CMD;
		i++;
		token_str = ft_strtok(NULL, " ");
	}
	tokens[i].type = END;
	return (tokens);
}
