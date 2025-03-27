/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:21:10 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/27 17:27:27 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {MAXC = 1024};

int	main()
{
	char	ps[MAXC] = "";
	char	*p = getenv("USER");
	char	*host = getenv("HOSTNAME");
	char	*s = NULL;
	int		count = 1;
	int		i = 0;

	sprintf(ps, "%d %s@%s> ", count, p, host);
	using_history();
	while ((s = readline(ps)))
	{
		if (strcmp(s, "quit") == 0)
		{
			free(s);
			break ;
		}
		add_history(s);
		free(s);
		count++;
		sprintf(ps, "%d %s@%s> ", count, p, host);
	}
	clear_history();
	return (0);
}
