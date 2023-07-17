/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:49:58 by mallaoui          #+#    #+#             */
/*   Updated: 2022/11/25 15:56:45 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *store)
{
	char	*temp;
	int		c;

	temp = malloc ((size_t)BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	c = 0;
	while (!ft_strchr_x(store, '\n'))
	{
		c = read(fd, temp, BUFFER_SIZE);
		if (c == 0)
			return (free(temp), store);
		if (c == -1)
			return (free(temp), free(store), NULL);
		temp[c] = '\0';
		store = ft_strjoin_x(store, temp);
	}
	return (free(temp), store);
}

char	*return_line(char *store)
{
	int		i;
	char	*p;
	int		j;

	i = 0;
	j = 0;
	while (store[j] && store[j] != '\n')
		j++;
	if (store[j] == '\n')
		j++;
	p = malloc (j + 1);
	if (!p)
		return (NULL);
	while (i < j)
	{
		p[i] = store[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*the_rest(char *store)
{
	int		i;
	char	*p;

	i = 0;
	p = store;
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\0' || store[i + 1] == '\0')
		return (free(store), NULL);
	i++;
	store = ft_strdup_x(&store[i]);
	free(p);
	return (store);
}

char	*get_next_line(int fd)
{
	static char		*store;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_file(fd, store);
	if (!store)
		return (NULL);
	line = return_line(store);
	store = the_rest(store);
	return (line);
}
