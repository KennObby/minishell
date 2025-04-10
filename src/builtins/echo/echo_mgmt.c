/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:34:41 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/07 13:22:39 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	handle_single_quotes(t_node *cmd, t_env **env)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[1], "'"))

	}
}
