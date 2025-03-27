/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:28:01 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/09 17:38:26 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *src, const char *dest, size_t length)
{
	size_t	i;

	i = 0;
	if (length == 0)
		return (0);
	while (i < length)
	{
		if (src[i] != dest[i])
			return ((unsigned char)src[i] - (unsigned char)dest[i]);
		if (src[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
