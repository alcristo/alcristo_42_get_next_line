/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcristo <alcristo@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:57:29 by alcristo          #+#    #+#             */
/*   Updated: 2026/06/19 11:53:09 by alcristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char const *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(char const *s)
{
	char	*dup;
	size_t	i;

	dup = malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	nlen;
	size_t	i;
	char	*subs;

	if (!s)
		return (ft_strdup(""));
	if (start > ft_strlen(s))
		nlen = 0;
	else if (ft_strlen(&s[start]) <= len)
		nlen = ft_strlen(&s[start]);
	else
		nlen = len;
	subs = malloc(nlen + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < nlen)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

char	*ft_strjoin(char const *dst, char const *src)
{
	char	*new;
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	new = malloc(len_d + len_s + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < len_d)
	{
		new[i] = dst[i];
		i++;
	}
	i = 0;
	while (i < len_s)
	{
		new[i + len_d] = src[i];
		i++;
	}
	new[len_d + len_s] = '\0';
	return (new);
}
