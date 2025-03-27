/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:53:47 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/14 23:25:41 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t	i;

	i = 0;
	if (dest == src || size == 0)
		return (dest);
	if (dest < src)
	{
		while (i < size)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else
	{
		i = size;
		while (i > 0)
		{
			i--;
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		}
	}
	return (dest);
}
