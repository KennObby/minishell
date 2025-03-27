/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:34:27 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/05 15:35:01 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	int	len;

	len = 0;
	if (!ptr)
		len += ft_putstr("(nil)");
	else
	{
		len += ft_putstr("0x");
		len += ft_puthex_lower((unsigned long long)ptr);
	}
	return (len);
}
