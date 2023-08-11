/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:14:13 by mallaoui          #+#    #+#             */
/*   Updated: 2022/11/24 21:58:48 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_x(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_x(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin_x(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*s3;

	i = 0;
	j = 0;
	k = 0;
	if (!s1)
		s1 = ft_strdup_x("");
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	s3 = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		s3[k++] = s1[i++];
	while (s2[j])
		s3[k++] = s2[j++];
	return (s3[k] = '\0', free(s1), s3);
}

char	*ft_strdup_x(char *s1)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)malloc(sizeof(char) * (ft_strlen_x(s1) + 1));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
