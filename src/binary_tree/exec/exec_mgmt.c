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

int	execute(t_node *node, t_env **env)
{
	int	status;

	if (!node)
	{
		ft_putendl_fd("minishell: NULL command node", 2);
		return (127);
	}
	if (node->type == CMD)
	{
		if (is_parent_only_builtin(node->args[0]))
		{
			status = execute_is_parent_only_builtin(node, env);
			return (status);
		}
		else if (is_forkable_builtin(node->args[0]))
			return (execute_forked_builtin(node, env));
		else
			return (execute_cmd(node, *env));
	}
	if (node->type == PIPE)
		return (execute_pipe(node, *env));
	if (node->type == SEMICOLON)
		return (execute_semicolon(node, *env));
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		return (execute_logical(node, *env));
	return (0);
}

int	execute_is_parent_only_builtin(t_node *cmd, t_env **env)
{
	int	status;
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (handle_redirections(cmd) != 0)
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	status = exec_builtin(cmd, env);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (status);
}

int	execute_forked_builtin(t_node *cmd, t_env **env)
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
		if (handle_redirections(cmd) != 0)
			exit(1);
		exit(exec_builtin(cmd, env));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
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
