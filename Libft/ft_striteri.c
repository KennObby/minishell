/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 20:49:35 by oilyine-          #+#    #+#             */
/*   Updated: 2024/10/31 21:18:37 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	len;
	size_t	index;

	if (!s || !f)
		return ;
	len = ft_strlen(s);
	index = 0;
	while (index < len)
	{
		f((unsigned int)index, &s[index]);
		index++;
	}
}
/*
void	to_case_base_on_index(unsigned int index, char *c)
{
	if (index % 2 == 0)
		*c = (char)ft_toupper((unsigned char)*c);
	else
	 	*c = (char)ft_tolower((unsigned char)*c);
}

int	main(void)
{
	char mutable_str[] = "Hello, World!";

	printf("Before ft_striteri: %s\n", mutable_str);

	ft_striteri(mutable_str, to_case_base_on_index);

	printf("After ft_striteri: %s\n", mutable_str);

	return (0);
}
*/
