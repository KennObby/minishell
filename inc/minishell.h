/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:01:37 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/25 10:04:49 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//< ----------------------- INCLUDES -------------------- >
# include <stdio.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../Libft/libft.h"
# include "../Libft/ft_printf.h"
# include "../Libft/get_next_line_bonus.h"

//< ----------------------- STRUCTS --------------------- >

/*
 * CMD = a simple command like cd 
 * PIPE = |
 * SEMICOLON = ;
 * LOGICAL_AND = &&
 * LOGICAL_OR = ||
 * REDIRECT_IN = <
 * REDIRECT_OUT = >
 * APPEND = >>
 * HEREDOC = <<
 * GROUPING = ( )
 *
 */

typedef enum e_type
{
	CMD,
	PIPE,
	SEMICOLON,
	LOGICAL_AND,
	LOGICAL_OR,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	GROUPING,
}				t_type;

/*
 * type = type tokenized in a node
 * args = args
 * writer = left child => output provider. related STDOUT_FILENO
 * reader = right child => input provider. related STDIN_FILENO
 */
typedef struct s_node
{
	t_type			type;
	char			**args;
	struct s_node	*writer;
	struct s_node	*reader;
}				t_node;

#endif
