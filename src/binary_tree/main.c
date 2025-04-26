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
#include <stdlib.h>
#include <unistd.h>

int	g_status = 0;

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
void	inter_mode(t_env *env_list)
{
	char		*input;
	char		*prompt;
	t_token		*tokens;
	t_node		*root;
	t_parser	parser;

	while (1)
	{
		prompt = built_prompt(env_list);
		setup_signals();
		signal(SIGQUIT, SIG_IGN);
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (ft_strlen(input))
			add_history(input);
		tokens = tokenize(input);
		free(input);
		if (!tokens)
			continue ;
		parser = (t_parser){tokens, 0};
		root = parse(&parser);
		if (!root)
		{
			free_tokens(tokens);
			continue ;
		}
		expand_node_args(root, env_list);
		prepare_heredocs(root);
		g_status = execute(root, &env_list);
		free_tokens(tokens);
		free_tree(root);
	}
}

void	non_inter_mode(t_env *env_list)
{
	char		*input;
	t_token		*tokens;
	t_node		*root;
	t_parser	parser;

	setup_signals();
	input = get_next_line(0);
	while (input != NULL)
	{
		if (input[0] == '\0' || input[0] == '\n')
		{
			free(input);
			input = get_next_line(0);
			continue ;
		}
		remove_newline(input);
		tokens = tokenize(input);
		free(input);
		if (!tokens)
		{
			input = get_next_line(0);
			continue ;
		}
		parser = (t_parser){tokens, 0};
		root = parse(&parser);
		if (!root)
		{
			free_tokens(tokens);
			input = get_next_line(0);
			continue ;
		}
		expand_node_args(root, env_list);
		prepare_heredocs(root);
		g_status = execute(root, &env_list);
		free_tokens(tokens);
		free_tree(root);
		input = get_next_line(0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env		*env_list;

	(void)ac;
	(void)av;
	env_list = init_env_list(envp);
	bump_shlvl(env_list);
	if (!isatty(0))
		non_inter_mode(env_list);
	else
		inter_mode(env_list);
	free_env_list(env_list);
	rl_clear_history();
	return (g_status);
}
