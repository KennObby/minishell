/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:10 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/30 17:50:39 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}
/*
int main(void)
{
	const char *str = "Bonjour le monde";
	unsigned int start = 8;
	size_t len = 2;
	char *sub;

	sub = ft_substr(str, start, len);
	if (sub)
	{
		printf("Sous-chaîne: \"%s\"\n", sub);
		free(sub); // Libération de la mémoire allouée
	}
	else
	{
		printf("Erreur d'allocation mémoire.\n");
	}
	return 0;
}
*/
