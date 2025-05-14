/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:57:57 by oilyine-          #+#    #+#             */
/*   Updated: 2025/05/14 01:04:43 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int	execute_subshell(t_data *d)
{
	pid_t	pid;
	int		status;
	t_node	*saved;

	pid = fork();
	saved = d->root;
	if (pid < 0)
	{
		perror("minishell");
		return (1);
	}
	if (pid == 0)
	{
		if (handle_redirections(saved) != 0)
			exit(g_data->exit_status);
		d->root = saved->writer;
		exit(execute(d));
	}
	waitpid(pid, &status, 0);
	d->root = saved;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_is_parent_only_builtin(t_data *d)
{
	if (handle_redirections(d->root) != 0)
	{
		dup2(d->stdin_backup, STDIN_FILENO);
		dup2(d->stdout_backup, STDOUT_FILENO);
		return (1);
	}
	g_data->exit_status = exec_builtin(d);
	dup2(d->stdin_backup, STDIN_FILENO);
	dup2(d->stdout_backup, STDOUT_FILENO);
	return (g_data->exit_status);
}

int	execute_forked_builtin(t_data *d)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		return (1);
	}
	if (pid == 0)
	{
		if (handle_redirections(d->root) != 0)
			exit(1);
		exit(exec_builtin(d));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
