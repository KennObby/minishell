/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembo    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:27:25 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/30 22:53:59 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*built_prompt(t_env *env)
{
	char	*home;
	char	cwd[MAX_PATH];
	char	*relative;
	char	*tmp;
	char	*prompt;

	home = get_env_value(env, "HOME");
	if (!getcwd(cwd, sizeof(cwd)))
		return (ft_strdup("minishell> "));
	if (home && ft_strcmp(cwd, home) == 0)
		return (ft_strdup("minishell> "));
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		relative = cwd + ft_strlen(home);
		tmp = ft_strjoin("~", relative);
		prompt = ft_strjoin(tmp, " > ");
		free(tmp);
		return (prompt);
	}
	return (ft_strjoin(cwd, " > "));
}

void	remove_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
/*
 * ast (root variable) = https://deepsource.com/glossary/ast
 *
 * non_interactive and interactive_mode => see isatty() func
 * https://medium.com/@santiagobedoa/coding-a-shell-using-c-1ea939f10e7e
 *
 * environment variables tried to be managed (char **envp)
 * !! -> Maybe considering to add env_list in s_env struct
 *
 */
void	inter_mode(t_data *d)
{
	while (1)
	{
		d->prompt = built_prompt(d->env_list);
		setup_signals();
		signal(SIGQUIT, SIG_IGN);
		d->input = readline(d->prompt);
		free(d->prompt);
		if (!d->input)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (*d->input)
			add_history(d->input);
		d->tokens = tokenize(d->input);
		free(d->input);
		if (!d->tokens)
			continue ;
		d->parser = (t_parser){d->tokens, 0};
		d->root = parse(&d->parser);
		if (!d->root)
		{
			free_tokens(d->tokens);
			g_data->exit_status = 2;
			continue ;
		}
		expand_node_args(d->root, d->env_list, &g_data->exit_status);
		expand_wildcards_node(d->root);
		prepare_heredocs(d->root);
		g_data->exit_status = execute(d);
		print_tree(d->root, 0);
		free_tokens(d->tokens);
		free_tree(d->root);
	}
}

void	non_inter_mode(t_data *d)
{
	char	*line;

	setup_signals();
	line = get_next_line(0);
	while (line != NULL)
	{
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			line = get_next_line(0);
			continue ;
		}
		remove_newline(line);
		d->tokens = tokenize(line);
		free(line);
		if (!d->tokens)
		{
			line = get_next_line(0);
			continue ;
		}
		d->parser = (t_parser){d->tokens, 0};
		d->root = parse(&d->parser);
		if (!d->root)
		{
			g_data->exit_status = 2;
			line = get_next_line(0);
			free_tokens(d->tokens);
			continue ;
		}
		expand_node_args(d->root, d->env_list, &g_data->exit_status);
		prepare_heredocs(d->root);
		g_data->exit_status = execute(d);
		free_tokens(d->tokens);
		free_tree(d->root);
		line = get_next_line(0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, envp);
	bump_shlvl(data.env_list);
	if (!isatty(0))
		non_inter_mode(&data);
	else
		inter_mode(&data);
	free_env_list(data.env_list);
	rl_clear_history();
	close(data.stdin_backup);
	close(data.stdout_backup);
	return (data.exit_status);
}
