/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristo <alcristo@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 09:47:39 by alcristo          #+#    #+#             */
/*   Updated: 2026/06/12 10:25:55 by alcristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_gnl
{
	char	*nxtl;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
}			t_gnl;
char	*get_next_line(int fd);
size_t	ft_strlen(char const *s);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strchr(char const *s, int c);
char	*ft_strdup(char const *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *dst, char const *src);

#endif
