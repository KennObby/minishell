/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:13:33 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/01 14:35:03 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_numb(long nb)
{
	size_t	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*ptr;
	long	nb;

	nb = n;
	len = ft_len_numb(nb);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = -nb;
	}
	while (len > (n < 0))
	{
		ptr[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (ptr);
}
/*
int main(void)
{
	int numbers[] = {0, 123, -456, INT_MAX, INT_MIN};
	size_t i;

	for (i = 0; i < sizeof(numbers)/sizeof(numbers[0]); i++)
	{
		char *str = ft_itoa(numbers[i]);
		if (str)
		{
			printf("ft_itoa(%d) = %s\n", numbers[i], str);
			// Pour INT_MIN, nous avons assigné une chaîne littérale,
			// donc pas besoin de libérer
			if (numbers[i] != INT_MIN)
				free(str);
		}
		else
		{
			printf("ft_itoa(%d) a échoué.\n", numbers[i]);
		}
	}
	return (0);
}
*/
