/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstarov <dstarov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:54:10 by dstarov           #+#    #+#             */
/*   Updated: 2023/05/01 14:43:41 by dstarov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_file(int fd, char *s)
{
	char	*buf;
	int		rd;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	rd = 1;
	while (rd != 0 && !ft_strchr(s, '\n'))
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buf);
			free(s);
			return (NULL);
		}
		buf[rd] = '\0';
		s = ft_strjoin(s, buf);
	}
	free(buf);
	return (s);
}

char	*single_line(char *s)
{
	char	*ptr;
	size_t	i;

	if (!*s)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	ptr = malloc(sizeof(char) * (i + 2));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*upd_s(char *s)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	ptr = malloc(sizeof(char) * (ft_strlen(s) + 1 - i));
	if (!ptr)
		return (NULL);
	i++;
	while (s[i])
		ptr[j++] = s[i++];
	ptr[j] = '\0';
	free(s);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*s[4242];
	char		*nl;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	s[fd] = read_file(fd, s[fd]);
	if (!s[fd])
		return (NULL);
	nl = single_line(s[fd]);
	s[fd] = upd_s(s[fd]);
	return (nl);
}
