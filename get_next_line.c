/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristo <alcristo@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 09:42:11 by alcristo          #+#    #+#             */
/*   Updated: 2026/06/15 11:00:17 by alcristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Fugas de memoria solucionadas. Falta ver por que paco da doble free.
Si elimino el free de la estructura reaparecen las fugas de memoria.
Problemas encntraados:
42_no_nl: No imprime la primera linea.
nl: No imprime el salto de linea.
multiple_line_no_nl: La ultima linea la imprime con el buffer.
big_line_no_nl: El buffer imprime al final.
alternate_line_nl_no_nl: solo imprime la primera/ultima linea.
alternate_line_nl_with_nl: ocurre lo mismo.
*/

static void	clear_line(t_gnl *gnl, size_t start)
{
	size_t	i;

	i = 0;
	while (gnl->line[i])
		gnl->line[i++] = '\0';
	gnl->buffer[start] = '\0';
	i = 0;
	while (gnl->buffer[start + i + 1])
	{
		gnl->line[i] = gnl->buffer[start + i + 1];
		gnl->buffer[i] = gnl->buffer[start + i + 1];
		i++;
	}
	while (gnl->buffer[i])
	{
		gnl->buffer[i] = '\0';
		gnl->line[i] = '\0';
		i++;
	}
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
	gnl->temp = gnl->line;
	gnl->line = ft_strjoin(gnl->line, gnl->buffer);
	free(gnl->temp);
	clear_line(gnl, i);
}

static char	*read_line(int fd, t_gnl *gnl)
{
	int	reading;

	reading = 1;
	while (reading > 0)
	{
		if (gnl->line && ft_strchr(gnl->line, '\n'))
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
			if (gnl->nxtl[0] == '\0' || reading == 0)
				return (NULL);
			return (gnl->nxtl);
		}
		gnl->temp = gnl->line;
		gnl->line = ft_strjoin(gnl->line, gnl->buffer);
		free(gnl->temp);
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
