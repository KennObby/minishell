/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:05:43 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/31 21:08:48 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute(t_data *d)
{
	char	*cmd;

	if (!d->root)
	{
		ft_putendl_fd("minishell: NULL command node", 2);
		return (g_data->exit_status = 127);
	}
	if (d->root->type == CMD)
	{
		cmd = NULL;
		if (d->root->args && d->root->args[0])
			cmd = d->root->args[0];
		if (cmd && is_parent_only_builtin(cmd))
			return (execute_is_parent_only_builtin(d));
		if (cmd && is_forkable_builtin(cmd))
			return (execute_forked_builtin(d));
		return (execute_cmd(d));
	}
	if (d->root->type == SUBSHELL)
		return (execute_subshell(d));
	if (d->root->type == PIPE)
		return (execute_pipe(d));
	if (d->root->type == SEMICOLON)
		return (execute_semicolon(d));
	if (d->root->type == LOGICAL_AND || d->root->type == LOGICAL_OR)
		return (execute_logical(d));
	return (0);
}

void	prepare_heredocs(t_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->type == CMD)
	{
		i = 0;
		while (i < node->redir_count)
		{
			if (node->redirs[i].type == HEREDOC)
				node->redirs[i].fd = handle_heredoc(node->redirs[i].filename);
			i++;
		}
	}
	prepare_heredocs(node->writer);
	prepare_heredocs(node->reader);
}

int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sig_handler);
		close(pipefd[0]);
		while (1)
		{
			line = readline(">");
			if (!line || ft_strcmp(line, delimiter) == 0)
				break ;
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		free(line);
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (-1);
	return (pipefd[0]);
}
