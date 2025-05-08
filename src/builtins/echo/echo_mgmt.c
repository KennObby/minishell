/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:34:41 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/07 13:22:39 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdbool.h>
#include <stdlib.h>
/*
 * In C convention, '\'' represents a single quote (e.g: " ' ")
 * Like, every "valid escapes" character can be isloated this way.
 * Those are the single && double quotes, backslash, Newline, Tab and null
 *
 * -> \', \", \\, \n, \t, \0
 *
 */
char	*extract_var_name(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len] && (ft_isalnum(s[len]) || s[len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	return (ft_substr(s, 0, len));
}
/*
 * This function has to be moved elsewhere (on utils ?)
 * expand_double_quoted has too much lines
 */
char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	if (!s1)
		return (ft_strdup(s2));
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}
/*
 * This functions heavy lifts of ->
 * 1 ) Parsing escapes mentionnned lines below
 * 2 ) Handles '$' edge cases by extracting the name variable
 * 3 ) Substition of strings if no characters looked for found
 *
 */
char	*expand_argument(const char *s, t_env **env)
{
	t_exp		state;

	state.result = ft_strdup("");
	state.in_single = false;
	state.in_double = false;
	state.i = 0;
	while (s[state.i])
	{
		if (s[state.i] == '\\' && !state.in_single)
			handle_escape(s, &state);
		else if (s[state.i] == '\'')
		{
			if (state.in_double)
				append_char(&state, s[state.i]);
			else
				handle_quote(s[state.i], &state);
		}
		else if (s[state.i] == '"')
		{
			if (state.in_single)
				append_char(&state, s[state.i]);
			else
				handle_quote(s[state.i], &state);
		}
		else if (s[state.i] == '$' && !state.in_single)
			handle_dollar(s, &state, env);
		else
			append_char(&state, s[state.i]);
		state.i++;
	}
	return (state.result);
}

void	handle_dollar(const char *s, t_exp *state, t_env **env)
{
	char	*var_part;
	char	*var_name;
	char	*var_value;

	state->i++;
	var_name = NULL;
	var_value = NULL;
	var_part = NULL;
	if (s[state->i] == '?')
		var_part = ft_itoa(g_data->exit_status);
	else if (ft_isalpha(s[state->i]) || s[state->i] == '_')
	{
		var_name = extract_var_name(s + state->i);
		if (var_name)
		{
			var_value = get_env_value(*env, var_name);
			state->i += ft_strlen(var_name) - 1;
			if (var_value)
				var_part = ft_strdup(var_value);
			else
				var_part = ft_strdup("");
			free(var_name);
		}
	}
	else
		var_part = ft_strdup("$");
	state->result = ft_strjoin_free(state->result, var_part);
	free(var_part);
}

void	handle_quote(char quote, t_exp *state)
{
	if (quote == '\'')
	{
		if (!state->in_double)
			state->in_single = !state->in_single;
	}
	else
	{
		if (!state->in_single)
			state->in_double = !state->in_double;
	}
}

void	handle_escape(const char *s, t_exp *state)
{
	if (s[state->i])
	{
		append_char(state, s[state->i]);
		state->i++;
	}
}

void	append_char(t_exp *state, char c)
{
	char	*joined;
	char	tmp[2];

	if (c == '\0')
		return ;
	if (state->in_single && (c == '*'))
		c = (char)(~c);
	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(state->result, tmp);
	free(state->result);
	state->result = joined;
}
