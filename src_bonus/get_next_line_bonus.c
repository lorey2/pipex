/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:08:26 by lorey             #+#    #+#             */
/*   Updated: 2024/11/25 16:38:57 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		bytes_read;

	i = 0;
	buffer = (char *)malloc(1024);
	bytes_read = read(0, &buffer[i], 1);
	if (!buffer || bytes_read < 1)
		return (bytes_read);
	while (bytes_read > 0 && buffer[i] != '\n')
		bytes_read = read(0, &buffer[++i], 1);
	if (buffer[i] == '\n')
		i++;
	buffer[i] = '\0';
	*line = buffer;
	if (bytes_read == 0 && i == 0)
	{
		free(buffer);
		*line = NULL;
		return (0);
	}
	return (1);
}
