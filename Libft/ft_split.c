/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:11:00 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/31 17:45:57 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	nbr_words;
	int	i;

	nbr_words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			nbr_words++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (nbr_words);
}

void	ft_free(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	find_next_word(const char *s, char c, int *start, int *len)
{
	*len = 0;
	while (s[*start] == c)
		(*start)++;
	while (s[*start + *len] != '\0' && s[*start + *len] != c)
		(*len)++;
}

char	*allocate_words(const char *s, int start, int length)
{
	char	*word;
	int		j;

	word = (char *)malloc((length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < length)
	{
		word[j] = s[start + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		nbr_words;
	int		i;
	int		start;
	int		len;

	if (!s)
		return (NULL);
	nbr_words = count_words(s, c);
	tab = (char **)malloc((nbr_words + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	start = 0;
	while (i < nbr_words)
	{
		find_next_word(s, c, &start, &len);
		tab[i] = allocate_words(s, start, len);
		if (!tab[i])
			ft_free(tab, i);
		start += len;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
/*
int	main(void)
{
	char	**result;
	int		i;

	result = ft_split("  Hello  world  this is   C  ", ' ');
	if (result == NULL)
	{
		printf("Allocation failed.\n");
		return (1);
	}
	i = 0;
	while (result[i] != NULL)
	{
		printf("Word %d: %s\n", i, result[i]);
		i++;
	}
	// Libération de la mémoire
	ft_free(result, i);
	return (0);
}
*/
