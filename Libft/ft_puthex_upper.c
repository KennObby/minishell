/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:23:05 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/05 23:13:42 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_hex_char_upper(int remainder)
{
	if (remainder < 10)
		return ('0' + remainder);
	else
		return ('A' + (remainder - 10));
}

int	ft_puthex_upper(unsigned long long nb)
{
	char	hex_digits[17];
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (nb <= 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (nb > 0)
	{
		hex_digits[i] = get_hex_char_upper(nb % 16);
		i++;
		nb = nb / 16;
	}
	len = i;
	while (--i >= 0)
		ft_putchar(hex_digits[i]);
	return (len);
}
