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

#include "../../inc/minishell.h"

void	execute_cmd(t_node *cmd, t_env *env_list)
{
	char	*cmd_path;
	char	**envp;
	int		status;
	pid_t	pid;

	if (handle_redirections(cmd) != 0)
		return ;
	cmd_path = resolve_path(cmd->args[0], env_list);
	if (!cmd_path)
	{
		ft_printf("minishell: command not found: %s\n", cmd->args[0]);
		return ;
	}
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(cmd, env_list);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		envp = env_list_to_array(env_list);
		if (execve(cmd_path, cmd->args, envp) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	else
		waitpid(pid, &status, 0);
}

void	execute_pipe(t_node *pipe_node, t_env *env)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fd) == -1)
	{
		perror("minishell");
		return ;
	}
	pid_left = fork();
	if (pid_left == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(pipe_node->writer, env);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execute(pipe_node->reader, env);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}

/* DOCS : WIFEXITED && WEXITSTATUS-> A voir si macros interdites...
 * 		Si c'est le cas, le code sera a repenser voir recreer ces macros
 * https://sites.uclouvain.be/SystInfo/usr/include/bits/waitstatus.h.html
 */
void	execute_logical(t_node *logical_node, t_env *env)
{
	int		status;

	execute(logical_node->writer, env);
	wait(&status);
	if (logical_node->type == LOGICAL_AND && WIFEXITED(status)
		&& WEXITSTATUS(status) == 0)
		execute(logical_node->reader, env);
	else if (logical_node->type == LOGICAL_OR && WIFEXITED(status)
		&& WEXITSTATUS(status) != 0)
		execute(logical_node->reader, env);
}

void	execute_semicolon(t_node *semi_node, t_env *env)
{
	execute(semi_node->writer, env);
	execute(semi_node->reader, env);
}

int	handle_redirections(t_node *cmd)
{
	int	fd;
	int	i;

	i = -1;
	while (++i < cmd->redir_count)
	{
		if (cmd->redirs[i].type == REDIRECT_OUT)
			fd = open(cmd->redirs[i].filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmd->redirs[i].type == APPEND)
			fd = open(cmd->redirs[i].filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (cmd->redirs[i].type == REDIRECT_IN)
			fd = open(cmd->redirs[i].filename, O_RDONLY);
		else if (cmd->redirs[i].type == HEREDOC)
			fd = handle_heredoc(cmd->redirs[i].filename);
		if (fd == -1)
		{
			perror("minishell");
			return (-1);
		}
		if (cmd->redirs[i].type == REDIRECT_IN
			|| cmd->redirs[i].type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
