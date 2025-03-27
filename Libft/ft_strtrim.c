/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:22:06 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/31 16:07:35 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_trimlen(const char *s1, const char *set)
{
	const char	*start;
	const char	*end;

	start = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (end > start && ft_strchr(set, *end))
		end--;
	return (end - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_trimlen(s1, set);
	res = ft_substr(s1, 0, len);
	return (res);
}
