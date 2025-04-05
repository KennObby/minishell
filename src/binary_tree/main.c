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

void	print_tree(t_node *node, int depth)
{
	int	i;

	if (!node)
		return ;
	ft_printf("\n");
	//print_tree(node->reader, depth + 4);
	i = 0;
	while (i < depth)
	{
		ft_printf(" ");
		i++;
	}
	if (node->type == CMD)
	{
		ft_printf("CMD: ");
		i = 0;
		while (node->args[i])
		{
			ft_printf("%s ", node->args[i]);
			i++;
		}
		i = 0;
		while (i < node->redir_count)
		{
			ft_printf("[%s %s]", redir_type_str(node->redirs[i].type),
				node->redirs[i].filename);
			i++;
		}
		ft_printf("\n");
	}
	else
	{
		ft_printf("OP: %s\n", type_to_str(node->type));
		print_tree(node->writer, depth + 1);
		print_tree(node->reader, depth + 1);
	}
	//print_tree(node->writer, depth + 4);
}
/*
 * ast = https://deepsource.com/glossary/ast 
 * environment variables tried to be managed (char **envp)
 * !! -> Maybe considering to add env_list in s_env struct
 *
 */
int	main(int ac, char **av, char **envp)
{
	char		*rl;
	t_token		*tokens;
	t_parser	parser;
	t_node		*ast;
	t_env		*env_list;

	(void)ac;
	(void)av;
	env_list = init_env_list(envp);
	while ((rl = readline("minishell> ")) != NULL)
	{
		if (ft_strlen(rl) > 0)
			add_history(rl);
		ft_printf("\n");
		tokens = tokenize(rl);
		parser = (t_parser){tokens, 0};
		ast = parse(&parser);
		//print_tree(ast, 0);
		execute(ast, env_list);
		bump_shlvl(env_list);
		free_tree(ast);
		free_tokens(tokens);
		free(rl);
	}
	free_env_list(env_list);
	return (0);
}
