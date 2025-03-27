/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:19:30 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/29 13:34:58 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;
	size_t	total_size;

	if (count != 0 && size > (size_t) - 1 / count)
		return (NULL);
	total_size = count * size;
	dest = (char *)malloc(total_size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, total_size);
	return (dest);
}
