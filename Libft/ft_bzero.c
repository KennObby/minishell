/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:29:18 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/01 23:52:48 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}
/*
int	main(void)
{
	char	str;

	str[50] = "nique ta mère simon";
	printf("output: %s\n", str);
	ft_bzero(str, 5);
	printf("output: %s\n", str);
	return (0);
}
*/
