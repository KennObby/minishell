/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:01:39 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/09 18:04:35 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int n)
{
	int		i;
	char	*last_occurence;

	i = 0;
	last_occurence = NULL;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)n)
			last_occurence = ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)n)
		last_occurence = ((char *)&str[i]);
	return (last_occurence);
}
