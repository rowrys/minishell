/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:52:31 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_new_buffer_gnl(char *buffer)
{
	char	*new_buffer;
	char	*endl;

	if (!buffer)
		return (NULL);
	new_buffer = NULL;
	endl = ft_strchr(buffer, '\n');
	if (endl && buffer[endl + 1 - buffer])
		new_buffer = ft_strdup(endl + 1);
	free(buffer);
	return (new_buffer);
}

static char	*get_line_gnl(char *line, char *buffer)
{
	char	*temp;
	char	*endl;
	size_t	size_line;
	size_t	buffer_part;

	size_line = ft_strlen(line);
	endl = ft_strchr(buffer, '\n');
	buffer_part = ft_strlen(buffer);
	if (endl)
		buffer_part = endl + 1 - buffer;
	temp = ft_calloc(sizeof(char), size_line + buffer_part + 1);
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	ft_strlcpy(temp, line, size_line + 1);
	ft_strlcat(temp, buffer, size_line + buffer_part + 1);
	free(line);
	return (temp);
}

static char	*read_gnl(int fd, char **line)
{
	char	*buffer;
	int		size_read;

	buffer = ft_calloc(sizeof(char), 8193);
	if (!buffer)
		return (NULL);
	size_read = read(fd, buffer, 8192);
	if (size_read < 0 && line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (size_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024] = {0};
	char		*line;

	if (fd < 0 || fd > 1024)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (!buffer[fd])
			buffer[fd] = read_gnl(fd, &line);
		if (!buffer[fd])
			break ;
		line = get_line_gnl(line, buffer[fd]);
		if (!line)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
			return (NULL);
		}
		buffer[fd] = get_new_buffer_gnl(buffer[fd]);
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}
