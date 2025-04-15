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
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
/* DOCS : https://sites.uclouvain.be/SystInfo/usr/include/bits/waitstatus.h.html
 */
int	execute_cmd(t_node *cmd, t_env *env_list)
{
	char	*cmd_path;
	char	**envp;
	int		status;
	pid_t	pid;

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
		envp = env_list_to_array(env_list);
		if (!cmd || !cmd->args || !cmd->args[0])
		{
			ft_printf("minishell: invalid command");
			exit(127);
		}
		if (ft_strchr(cmd->args[0], '/'))
		{
			if (access(cmd->args[0], X_OK) == 0)
				execve(cmd->args[0], cmd->args, envp);
			ft_printf("bash: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
		cmd_path = resolve_path(cmd->args[0], env_list);
		if (!cmd_path)
		{
			ft_printf("bash: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
		execve(cmd_path, cmd->args, envp);
		ft_printf("bash: command not found: %s\n", cmd_path);
		free(cmd_path);
		free_str_array(envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_pipe(t_node *pipe_node, t_env *env)
{
	int		fd[2];
	int		status;
	pid_t	pid_left;
	pid_t	pid_right;

	status = 0;
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
		exit(execute(pipe_node->writer, &env));
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit(execute(pipe_node->reader, &env));
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_logical(t_node *logical_node, t_env *env)
{
	int		status;

	status = execute(logical_node->writer, &env);
	if (logical_node->type == LOGICAL_AND && status == 0)
		return (execute(logical_node->reader, &env));
	else if (logical_node->type == LOGICAL_OR && status != 0)
		return (execute(logical_node->reader, &env));
	return (status);
}

int	execute_semicolon(t_node *semi_node, t_env *env)
{
	execute(semi_node->writer, &env);
	return (execute(semi_node->reader, &env));
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
		if (fd == -1)
		{
			ft_printf("bash: %s: No such file or directory", cmd->args[0]);
			exit (126);
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
