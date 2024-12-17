/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 02:15:32 by lorey             #+#    #+#             */
/*   Updated: 2024/11/27 13:09:50 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	check_p_a_t_h(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5))
			i++;
		else
			break ;
	}
	return (i);
}

void	setup_path(char **env, t_path_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 5;
	i = check_p_a_t_h(env);
	while (env[i][j])
		j++;
	data->path = malloc(sizeof(char) * (j - 4));
	if (!data->path)
		error("malloc error", data);
	j = 5;
	while (env[i][j])
	{
		data->path[j - 5] = env[i][j];
		j++;
	}
	data->path[j - 5] = '\0';
	data->path_split = ft_split(data->path, ':');
	if (!data->path_split)
		error("malloc error", data);
	free(data->path);
	data->nbr_malloc = 2;
}

void	setup_here_doc(t_path_data *data, int argc, char **argv)
{
	if (argc < 6)
		error("too less args hd", data);
	data->output_file = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (data->output_file == -1)
		error("file open error", data);
	here_doc(argv[2], data);
	data->process += 1;
}

void	free_double_point(char **point)
{
	int	j;

	j = -1;
	while (point[++j])
		free(point[j]);
	free(point);
}

void	error(char *message, t_path_data *data)
{
	if (data->nbr_malloc >= 2)
		free_double_point(data->path_split);
	if (message == NULL)
		exit(EXIT_SUCCESS);
	perror(message);
	exit(EXIT_FAILURE);
}
