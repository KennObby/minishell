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
#include <stdlib.h>
/*
 * In C convention, '\'' represents a single quote (e.g: " ' ")
 * Like, every "valid escapes" character can be isloated this way.
 * Those are the single && double quotes, backslash, Newline, Tab and null
 *
 * -> \', \", \\, \n, \t, \0
 *
 */
char	*handle_single_quotes(char *arg)
{
	int		i;
	int		len;

	len = ft_strlen(arg);
	i = 0;
	while (arg[i])
	{
		if (arg[0] == '\'' && arg[len - 1] == '\'')
			return (ft_substr(arg, 1, len - 2));
		i++;
	}
	return (arg);
}

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
char	*expand_double_quoted(const char *s, t_env **env)
{
	char	*result;
	int		i;
	char	*tmp;
	char	*name;
	char	*value;

	result = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && (s[i + 1] == '$'
				|| s[i + 1] == '"' || s[i + 1] == '\\'))
		{
			tmp = ft_substr(s, i + 1, 1);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
			i += 2;
		}
		else if (s[i] == '$')
		{
			i++;
			name = extract_var_name(&s[i]);
			if (!name)
			{
				result = ft_strjoin_free(result, "$");
				continue ;
			}
			if (ft_strlen(name) == 0)
			{
				free(name);
				result = ft_strjoin_free(result, "$");
				continue ;
			}
			value = get_env_value(*env, name);
			if (value)
				result = ft_strjoin_free(result, value);
			else
				result = ft_strjoin_free(result, "");
			i += ft_strlen(name);
			free(name);
		}
		else
		{
			tmp = ft_substr(s, i, 1);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
			i++;
		}
	}
	ft_printf(">> expanding quotes: %s\n", s);
	free((char *)s);
	return (result);
}

char	*handle_double_quotes(char *arg, t_env **env)
{
	char	*stripped;

	if (!arg || ft_strlen(arg) < 2)
		return (ft_strdup(arg));
	if (arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"')
		stripped = ft_substr(arg, 1, ft_strlen(arg) - 2);
	else
		return (ft_strdup(arg));
	if (!stripped)
		return (NULL);
	ft_printf(">> stripped: = %s\n", stripped);
	return (expand_double_quoted(stripped, env));
}
