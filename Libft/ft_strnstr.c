/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:08:10 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/12 21:54:17 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;
	size_t	j;

	needle_len = 0;
	while (needle[needle_len])
		needle_len++;
	if (needle_len == 0)
		return ((char *)haystack);
	i = 0;
	while (i + needle_len <= len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = 1;
			while (j < needle_len && (i + j) < len
				&& haystack[i + j] == needle[j])
				j++;
			if (j == needle_len)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
