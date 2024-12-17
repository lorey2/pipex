/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:44:31 by lorey             #+#    #+#             */
/*   Updated: 2024/11/25 17:01:24 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;

	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!result)
		return (0);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	result[i] = '/';
	i = -1;
	while (s2[++i])
		result[i + ft_strlen(s1) + 1] = s2[i];
	result[i + ft_strlen(s1) + 1] = '\0';
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
