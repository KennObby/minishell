/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:55:22 by oilyine-          #+#    #+#             */
/*   Updated: 2025/04/17 16:42:54 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 130;
}

void	heredoc_sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

/* The Linux Programming Interface, Page 390
 *
 * SIGINT = CTRL-C (Terminal interrupt. value = 2)
 * SIGQUIT = CTRL-\ (Terminal quit. value = 3)
 * SIG_IGN = Ignores the signal 
 * SIG_DFL -> Restore signal disposition de default
 */
void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
