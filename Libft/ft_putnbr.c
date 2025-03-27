/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:42:11 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/05 11:47:03 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	ft_putnbr_rec(unsigned long nbr)
{
	if (nbr >= 10)
		return (ft_putnbr_rec(nbr / 10) + ft_putchar('0' + (nbr % 10)));
	return (ft_putchar('0' + nbr));
}

int	ft_putnbr(int nb)
{
	int					len;
	unsigned long long	nbr;

	len = 0;
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putstr("2147483648");
		return (11);
	}
	if (nb < 0)
	{
		ft_putchar('-');
		len++;
		nbr = -((long long)nb);
	}
	else
	{
		nbr = nb;
	}
	len += ft_putnbr_rec(nbr);
	return (len);
}
