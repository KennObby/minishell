/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:15:09 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/01 22:28:20 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	size_t	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		*(unsigned char *)(ptr + i) = (unsigned char)value;
		i++;
	}
	return (ptr);
}
