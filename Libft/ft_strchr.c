/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:06:32 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/06 23:38:01 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int n)
{
	char	target;
	int		i;

	i = 0;
	target = (char)n;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == target)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == target)
		return ((char *)&str[i]);
	return (NULL);
}
