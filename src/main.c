/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:27:25 by oilyine-          #+#    #+#             */
/*   Updated: 2025/03/28 23:06:32 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include "../Libft/ft_printf.h"

int	main(void)
{
	char	*rl;

	rl = readline("Prompt > ");
	ft_printf("%s\n", rl);
	return (0);
}
