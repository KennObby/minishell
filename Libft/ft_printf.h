/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:23:22 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/05 23:15:01 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putnbr(int nb);
int		ft_putunbr(unsigned int nb);
int		ft_putstr(char *s);
int		ft_putptr(void *ptr);
int		ft_puthex_lower(unsigned long long nb);
int		ft_puthex_upper(unsigned long long nb);

#endif
