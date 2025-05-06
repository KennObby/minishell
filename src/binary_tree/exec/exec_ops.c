/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:09:25 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/31 23:22:07 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
/* DOCS : https://sites.uclouvain.be/SystInfo/usr/include/bits/waitstatus.h.html
 */
int	execute_cmd(t_data *d)
{
	pid_t	pid;
	char	**envp;
	char	*path;
	int		redir_status;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		return (g_data->exit_status = 1);
	}
	if (pid == 0)
	{
		redir_status = handle_redirections(d->root);
		if (redir_status != 0)
		{
			dup2(d->stdin_backup, STDIN_FILENO);
			dup2(d->stdout_backup, STDOUT_FILENO);
			g_data->exit_status = redir_status;
			exit(redir_status);
		}
		envp = env_list_to_array(d->env_list);
		if (!d->root->args || !d->root->args[0])
		{
			ft_putstr_fd("minishell: invalid command\n", 2);
			exit(127);
		}
		if (ft_strchr(d->root->args[0], '/'))
		{
			if (access(d->root->args[0], X_OK))
			{
				reset_signals();
				execve(d->root->args[0], d->root->args, envp);
			}
			perror(d->root->args[0]);
			exit(126);
		}
		path = resolve_path(d->root->args[0], d->env_list);
		if (!path)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			exit(127);
		}
		reset_signals();
		execve(path, d->root->args, envp);
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		return (g_data->exit_status = 128 + WTERMSIG(status));
	else
		g_data->exit_status = 1;
	return (g_data->exit_status);
}

int	execute_pipe(t_data *d)
{
	t_node	*full_tree;
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	if (pipe(fd) == -1)
	{
		perror("minishell");
		return (1);
	}
	pid_left = fork();
	if (pid_left == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		full_tree = d->root;
		d->root = full_tree->writer;
		status_left = execute(d);
		free_tokens(d->tokens);
		free_tree(full_tree);
		exit(status_left);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		full_tree = d->root;
		d->root = full_tree->reader;
		status_right = execute(d);
		free_tokens(d->tokens);
		free_tree(full_tree);
		exit(status_right);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFEXITED(status_right))
		g_data->exit_status = WEXITSTATUS(status_right);
	else if (WIFSIGNALED(status_right))
		g_data->exit_status = 128 + WTERMSIG(status_right);
	else
		g_data->exit_status = 1;
	return (g_data->exit_status);
}

int	execute_logical(t_data *d)
{
	t_node	*saved;
	int		status;

	saved = d->root;
	d->root = saved->writer;
	status = execute(d);
	if (saved->type == LOGICAL_AND)
	{
		if (status == 0)
		{
			d->root = saved->reader;
			status = execute(d);
		}
	}
	else if (saved->type == LOGICAL_OR)
	{
		if (status != 0)
		{
			d->root = saved->reader;
			status = execute(d);
		}
	}
	d->root = saved;
	return (g_data->exit_status = status);
}

int	execute_semicolon(t_data *d)
{
	t_node	*saved;
	int		status;

	saved = d->root;
	d->root = saved->writer;
	(void)execute(d);
	d->root = saved->reader;
	status = execute(d);
	d->root = saved;
	return (g_data->exit_status = status);
}

int	handle_redirections(t_node *cmd)
{
	int	fd;
	int	i;

	i = 0;
	if ((cmd->redirs == NULL && cmd->redir_count > 0))
	{
		ft_printf("minishell: redirection: invalid command\n");
		return (-1);
	}
	while (i < cmd->redir_count)
	{
		fd = -1;
		if (cmd->redirs[i].type == REDIRECT_OUT)
			fd = open(cmd->redirs[i].filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->redirs[i].type == APPEND)
			fd = open(cmd->redirs[i].filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (cmd->redirs[i].type == REDIRECT_IN)
			fd = open(cmd->redirs[i].filename, O_RDONLY);
		else if (cmd->redirs[i].type == HEREDOC)
			fd = cmd->redirs[i].fd;
		if (fd < 0)
		{
			perror(cmd->redirs[i].filename);
			if (errno == ENOENT)
				return (g_data->exit_status = 1);
			if (errno == EACCES)
				return (g_data->exit_status = 126);
			return (g_data->exit_status = 1);
		}
		if (cmd->redirs[i].type == REDIRECT_IN
			|| cmd->redirs[i].type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
	return (0);
}
