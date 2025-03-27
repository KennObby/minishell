/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:05:03 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/05 13:08:09 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	ft_get_digit_char(int remainder)
{
	return ('0' + remainder);
}

int	ft_putunbr(unsigned int nb)
{
	char	digits[10];
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (nb > 0)
	{
		digits[i++] = ft_get_digit_char(nb % 10);
		nb /= 10;
	}
	len += i;
	while (--i >= 0)
	{
		ft_putchar(digits[i]);
	}
	return (len);
}
