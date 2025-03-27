/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:06:47 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/19 14:40:40 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FD_SIZE
#  define FD_SIZE 1024
# endif

size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *str, int n);
char		*ft_strdup(const char *s1);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strjoin(const char *s1, const char *s2);
char		*fill_line_buffer(int fd, char **left_c, char *buffer);
char		*get_next_line(int fd);

#endif
