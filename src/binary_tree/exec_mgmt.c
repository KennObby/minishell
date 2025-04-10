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

#include "../../inc/minishell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute(t_node *node, t_env **env)
{
	int	saved_in;
	int	saved_out;
	int	status;

	if (!node)
		return (0);
	if (node->type == CMD)
	{
		if (is_parent_only_builtin(node->args[0]))
		{
			saved_in = dup(STDIN_FILENO);
			saved_out = dup(STDOUT_FILENO);
			if (handle_redirections(node) != 0)
				return (1);
			status = exec_builtin(node, env);
			dup2(saved_in, STDIN_FILENO);
			dup2(saved_out, STDOUT_FILENO);
			close(saved_in);
			close(saved_out);
			return (status);
		}
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

	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			write(1, "\n", 1);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}
