/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:43:56 by oilyine-          #+#    #+#             */
/*   Updated: 2025/05/01 11:47:53 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <unistd.h>

t_data	*g_data = NULL;

void	init_data(t_data *d, char **envp)
{
	g_data = d;
	d->pid = 0;
	d->env_list = init_env_list(envp);
	ensure_minimal_env(&d->env_list);
	d->tokens = NULL;
	d->root = NULL;
	d->input = NULL;
	d->prompt = NULL;
	d->exit_status = 0;
	d->pipes = NULL;
	d->nb_pipes = 0;
	d->stdin_backup = dup(STDIN_FILENO);
	d->stdout_backup = dup(STDOUT_FILENO);
}
