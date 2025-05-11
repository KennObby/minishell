/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:48:58 by oilyine-          #+#    #+#             */
/*   Updated: 2025/05/01 15:49:20 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

int	builtin_exit(t_data *d)
{
	ft_putendl_fd("exit", 1);
	exit_mgmt(d);
	return (d->exit_status);
}

void	exit_mgmt(t_data *d)
{
	char		*arg;
	int			i;
	bool		has_digit;
	long long	value;

	arg = d->root->args[1];
	if (arg)
	{
		i = 0;
		if (arg[i] == '+' || arg[i] == '-')
			i++;
		has_digit = true;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
			{
				has_digit = false;
				break ;
			}
			i++;
		}
		if (!has_digit)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		if (d->root->args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			d->exit_status = 1;
			return ;
		}
		value = ft_atoll(arg);
		d->exit_status = (int)value;
	}
	exit((unsigned char)d->exit_status);
}
