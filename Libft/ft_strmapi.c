/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 20:27:24 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/31 20:49:15 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	index;
	char	*mapi;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	mapi = malloc(sizeof(char) * (len + 1));
	if (!mapi)
		return (NULL);
	index = 0;
	while (index < len)
	{
		mapi[index] = f((unsigned int)index, s[index]);
		index++;
	}
	mapi[len] = '\0';
	return (mapi);
}
/*
char	to_upper_with_index(unsigned int index, char c)
{
	(void)index;
	if (c >= 'a' && c <= 'z')
		return ((char)(c - 32));
	return (c);
}

int	main(void)
{
	const char	*original_str = "Hello, World!";
	char		*mapped_str;

	printf("Original String %s\n, original_str");
	mapped_str = ft_strmapi(original_str, to_upper_with_index);
	if (mapped_str)
	{
		printf("ft_strmapi : %s\n", mapped_str);
		free(mapped_str);
	}
	else
		printf("Echec d'allocation de memoire de la ft_strmapi. \n");
	return (0);
}
*/
