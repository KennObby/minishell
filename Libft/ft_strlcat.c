/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:12:10 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/04 19:57:46 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	space_left;

	if (!dest || !src)
		return (0);
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (dest_len >= size)
		return (size + src_len);
	space_left = size - dest_len - 1;
	if (space_left > 0)
	{
		if (src_len < space_left)
		{
			ft_memcpy(dest + dest_len, src, src_len + 1);
		}
		else
		{
			ft_memcpy(dest + dest_len, src, space_left);
			dest[dest_len + space_left] = '\0';
		}
	}
	return (dest_len + src_len);
}
