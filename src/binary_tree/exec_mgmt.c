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

void	execute(t_node *node, t_env *env)
{
	if (!node)
		return ;
	if (node->type == CMD)
		execute_cmd(node, env);
	if (node->type == PIPE)
		execute_pipe(node, env);
	if (node->type == SEMICOLON)
		execute_semicolon(node, env);
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
		execute_logical(node, env);
}

int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		pipefd[2];

	pipe(pipefd);
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
	return (pipefd[0]);
}
