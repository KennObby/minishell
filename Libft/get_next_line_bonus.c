/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:05:12 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/19 14:40:19 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

char	*fill_line_buffer(int fd, char **left_c, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			if (*left_c)
				free(*left_c);
			return (*left_c = NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!*left_c)
			*left_c = ft_strdup("");
		tmp = *left_c;
		*left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*left_c);
}

static char	*line_extractor(char **line_buffer)
{
	char	*line;
	char	*tmp;
	size_t	len;

	len = 0;
	if (!**line_buffer || !*line_buffer || !line_buffer)
		return (NULL);
	while ((*line_buffer)[len] && (*line_buffer)[len] != '\n')
		len++;
	if ((*line_buffer)[len] == '\n')
		len++;
	line = ft_substr(*line_buffer, 0, len);
	if ((*line_buffer)[len] != '\0')
		tmp = ft_strdup(*line_buffer + len);
	else
		tmp = ft_strdup("");
	free(*line_buffer);
	*line_buffer = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_c[FD_SIZE];
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_SIZE)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, &left_c[fd], buffer);
	free (buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	line = line_extractor(&left_c[fd]);
	if (left_c[fd] && left_c[fd][0] == '\0')
	{
		free(left_c[fd]);
		left_c[fd] = NULL;
	}
	return (line);
}
