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

int	execute(t_node *node, t_env **env)
{
	if (!node)
		return (0);
	if (node->type == CMD)
	{
		if (is_builtin(node->args[0]))
			return (exec_builtin(node, env));
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
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}
