/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:30:56 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/05 23:15:11 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_args(va_list *args, char c)
{
	int		len;

	len = 0;
	if (c == '%')
	{
		len += ft_putchar('%');
	}
	else if (c == 'c')
		len += ft_putchar(va_arg(*args, int));
	else if (c == 's')
		len += ft_putstr(va_arg(*args, char *));
	else if (c == 'p')
		len += ft_putptr(va_arg(*args, void *));
	else if (c == 'd' || c == 'i')
		len += ft_putnbr(va_arg(*args, int));
	else if (c == 'u')
		len += ft_putunbr(va_arg(*args, int));
	else if (c == 'x')
		len += ft_puthex_lower((unsigned int)
				va_arg(*args, unsigned long long));
	else if (c == 'X')
		len += ft_puthex_upper((unsigned int)
				va_arg(*args, unsigned long long));
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	len = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += get_args(&args, format[i + 1]);
			i++;
		}
		else
		{
			ft_putchar(format[i]);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
