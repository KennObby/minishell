/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oilyine-@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:13:56 by oilyine-          #+#    #+#             */
/*   Updated: 2025/02/09 13:31:44 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static int	get_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (10 + (c - 'a'));
	if (c >= 'A' && c <= 'F')
		return (10 + (c - 'A'));
	return (-1);
}

uint32_t	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	i;
	int	digit;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		digit = get_digit(str[i]);
		if (digit < 0 || digit >= base)
			break ;
		result = result * base + digit;
		i++;
	}
	return (result * sign);
}
