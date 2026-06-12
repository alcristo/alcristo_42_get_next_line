/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristo <alcristo@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 09:42:11 by alcristo          #+#    #+#             */
/*   Updated: 2026/06/12 17:45:24 by alcristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	clear_line(t_gnl *gnl, size_t start)
{
	size_t	i;

	i = 0;
	while (i <= start)
		gnl->line[i++] = '\0';
	i = 0;
	while (gnl->line[i + start + 1])
	{
		gnl->line[i] = gnl->line[i + start + 1];
		i++;
	}
/*	if (ft_strchr(gnl->line, '\n'))
	{
		while (gnl->line[i] && gnl->line[i] != '\n')
			i++;
	}
	i = 0;
	if (gnl->line[i] == '\n')
	{
		while (gnl->line[i])
		{
			gnl->line[i] = gnl->line[start + i];
			i++;
		}
		while (gnl->line[i])
			gnl->line[i++] = '\0';
	}
	else
	{
		while (gnl->line[i])
			gnl->line[i++] = '\0';
	}
	i = 0;
//	printf("Line before setting: %s/\n", gnl->line);
	while (gnl->line[i])
		gnl->line[i++] = '\0';
//	printf("Buffer before clearing: %s/\n", gnl->buffer);
	gnl->buffer[start] = '\0';
	i = 0;
	while (gnl->buffer[start + i + 1])
	{
		gnl->line[i] = gnl->buffer[start + i + 1];
		gnl->buffer[i] = gnl->buffer[start + i + 1];
		i++;
	}
//	printf("Line after setting: %s/\n", gnl->line);
	while (gnl->buffer[i])
	{
		gnl->buffer[i] = '\0';
		gnl->line[i] = '\0';
		i++;
	}
//	printf("Buffer after clearing: %s/\n", gnl->buffer);
*/
}

static void	end_of_line(t_gnl *gnl, int nwlns)
{
	size_t	i;

	i = 0;
	while (gnl->buffer[i] != '\n' && gnl->buffer[i])
		i++;
	if (nwlns == 0)
		gnl->nxtl = ft_strjoin(gnl->line, ft_substr(gnl->buffer, 0, i));
	else
		gnl->nxtl = ft_substr(gnl->line, 0, i);
	gnl->line = ft_strjoin(gnl->line, gnl->buffer);
	clear_line(gnl, i);
}

static char	*read_line(int fd, t_gnl *gnl)
{
	int	reading;

	reading = 1;
	while (reading > 0)
	{
		if (ft_strchr(gnl->line, '\n'))
		{
			end_of_line(gnl, 1);
			return (gnl->nxtl);
		}
		reading = read(fd, gnl->buffer, BUFFER_SIZE);
		if (reading < 0)
			return (NULL);
		if (ft_strchr(gnl->buffer, '\n') || reading < BUFFER_SIZE)
		{
			end_of_line(gnl, 0);
			if (gnl->nxtl[0] == '\0')
				return (NULL);
			return (gnl->nxtl);
		}
		gnl->line = ft_strjoin(gnl->line, gnl->buffer);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char			*nxtl;
	static t_gnl	*gnl;

	if (fd < 0)
		return (NULL);
	if (!gnl)
	{
		gnl = malloc(sizeof(t_gnl));
		if (!gnl)
			return (NULL);
		gnl->line = ft_strdup("\0");
	}
	nxtl = read_line(fd, gnl);
	if (!nxtl)
		free(gnl);
	return (nxtl);
}

/*
Esta funcion funciona perfectamente con tamaño de buffer = 1
Ahora falta que imprima toda la linea con cualquier tamaño de buffer
El remanente de la linea se guarda en la linea.

static void	end_of_line(char *line, t_gnl *gnl)
{
	size_t	i;

	i = 0;
	while (gnl->buffer[i] != '\n' && gnl->buffer[i])
		i++;
	gnl->nxtl = ft_strjoin(line, ft_substr(gnl->buffer, 0, i));
}

static char	*read_line(int fd, char *line, t_gnl *gnl)
{
	int		reading;

	reading = 1;
	while (reading > 0)
	{
		reading = read(fd, gnl->buffer, BUFFER_SIZE);
		if (reading < 0)
			return (NULL);
		if (ft_strchr(gnl->buffer, '\n') || reading == 0)
		{
			end_of_line(line, gnl);
			if (gnl->nxtl[0] == '\0')
				return (NULL);
			return (gnl->nxtl);
		}
		line = ft_strjoin(line, gnl->buffer);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*nxtl;
	t_gnl		*gnl;

	if (fd < 0)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	gnl = malloc(sizeof(t_gnl));
	if (!gnl)
		return (NULL);
	nxtl = read_line(fd, line, gnl);
	free(line);
	free(gnl);
	return (nxtl);
}
*/
