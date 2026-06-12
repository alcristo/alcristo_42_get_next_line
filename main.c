/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristo <alcristo@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:25:19 by alcristo          #+#    #+#             */
/*   Updated: 2026/06/12 14:52:47 by alcristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// ssize_t write(int fd, const void *buf, size_t count);
//  ssize_t read(int fd, const void *buf, size_t count);
int	main(void)
{
	char	*line;
	int	fd;
	int	i = 0;

	fd = open("text.txt", O_RDONLY);
	while (i > -1 && line)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
	}
	close(fd);
	free(line);
	return (0);
}
