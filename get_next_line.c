/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristo <alcristo@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 09:42:11 by alcristo          #+#    #+#             */
/*   Updated: 2026/06/22 15:43:20 by alcristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*end_of_line(char **stsh)
{
	size_t	pos;
	char	*temp;
	char	*line;

	pos = 0;
	temp = ft_strdup(*stsh);
	if (!temp)
		return (NULL);
	while (temp[pos] && temp[pos] != '\n')
		pos++;
	line = ft_substr(*stsh, 0, pos + 1);
	if (!line)
		return (free(temp), NULL);
	free(*stsh);
	*stsh = ft_substr(temp, pos + 1, ft_strlen(temp));
	if (!*stsh)
		return (free(temp), free(line), NULL);
	free(temp);
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

static char	*read_line(int fd, char **stsh)
{
	int		reading;
	char	*buff;
	char	*temp;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	reading = 1;
	while (reading > 0)
	{
		reading = read(fd, buff, BUFFER_SIZE);
		if (reading < 0)
			return (free(buff), NULL);
		buff[reading] = '\0';
		temp = *stsh;
		*stsh = ft_strjoin(temp, buff);
		if (!*stsh)
			return (free(buff), free(temp), NULL);
		free(temp);
		if (ft_strchr(*stsh, '\n') || reading < BUFFER_SIZE)
			return (free(buff), end_of_line(stsh));
	}
	return (free(buff), NULL);
}

char	*get_next_line(int fd)
{
	static char	*stsh;
	char		*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 0)
		return (NULL);
	if (!stsh)
	{
		stsh = ft_strdup("");
		if (!stsh)
			return (NULL);
	}
	if (ft_strchr(stsh, '\n'))
	{
		line = end_of_line(&stsh);
		if (!line)
			return (free(stsh), stsh = NULL, NULL);
		return (line);
	}
	line = read_line(fd, &stsh);
	if (!line && stsh)
		return (free(stsh), stsh = NULL, NULL);
	return (line);
}
