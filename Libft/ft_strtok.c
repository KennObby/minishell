/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:42:57 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/28 21:48:10 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*current;
	char		*token_start;

	if (str != NULL)
		current = str;
	if (current == NULL)
		return (NULL);
	while (*current && ft_strchr(delim, *current))
		current++;
	if (*current == '\0')
		return (NULL);
	token_start = current;
	while (*current && !ft_strchr(delim, *current))
		current++;
	if (*current)
	{
		*current = '\0';
		current++;
	}
	else
		current = NULL;
	return (token_start);
}
