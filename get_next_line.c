/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaoulea <ppaoulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:26:24 by ppaoulea          #+#    #+#             */
/*   Updated: 2025/06/21 15:45:28 by ppaoulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *stash)
{
	int		len;
	int		j;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < len)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*update_remainder(char *stash)
{
	int		i;
	int		j;
	char	*remainder;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	remainder = malloc(ft_strlen(stash + i) + 1);
	if (!remainder)
		return (NULL);
	j = 0;
	while (stash[i])
		remainder[j++] = stash[i++];
	remainder[j] = '\0';
	free(stash);
	return (remainder);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	char	*tmp;
	ssize_t	rb;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	rb = 1;
	while (!ft_strchr(stash, '\n') && rb > 0)
	{
		rb = read(fd, buf, BUFFER_SIZE);
		if (rb == -1)
			return (free(buf), free(stash), NULL);
		buf[rb] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		if (!stash)
			return (free(buf), NULL);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_remainder(stash);
	return (line);
}
