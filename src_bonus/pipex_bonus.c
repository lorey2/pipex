/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:02:04 by lorey             #+#    #+#             */
/*   Updated: 2024/11/27 13:15:33 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute(char *command, t_path_data *data)
{
	int		i;

	i = -1;
	while (data->path_split[++i])
	{
		data->path_with_com = ft_strjoin(data->path_split[i], command);
		if (!data->path_with_com)
			error("malloc error", data);
		data->path_with_com_split = ft_split(data->path_with_com, ' ');
		if (!data->path_with_com_split)
			error("malloc error", data);
		data->cmd_split = ft_split(command, ' ');
		if (!data->cmd_split)
			error("malloc error", data);
		if (execve(data->path_with_com_split[0], data->cmd_split, NULL) != -1)
			break ;
		free_double_point(data->path_with_com_split);
		free_double_point(data->cmd_split);
		free(data->path_with_com);
	}
	error("command not found", data);
}

static void	child_process(char *argv, t_path_data *data)
{
	pid_t	child_pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error("pipe_error", data);
	child_pid = fork();
	if (child_pid == -1)
		error("fork_error", data);
	if (child_pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(argv, data);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	here_doc(char *limiter, t_path_data *data)
{
	if (pipe(data->fd) == -1)
		error("pipe error hd", data);
	data->here_pid = fork();
	if (data->here_pid == 0)
	{
		close(data->fd[0]);
		while (get_next_line(&data->line))
		{
			if (ft_strncmp(data->line, limiter, ft_strlen(limiter)) == 0)
			{
				free(data->line);
				error(NULL, data);
			}
			write(data->fd[1], data->line, ft_strlen(data->line));
			free(data->line);
		}
		error("how did you get there?", data);
	}
	else
	{
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

static void	init(int argc, t_path_data *data, char **env)
{
	data->nbr_malloc = 0;
	data->process = 1;
	if (argc < 5)
		error("too less args", data);
	setup_path(env, data);
}

int	main(int argc, char **argv, char **env)
{
	t_path_data	data;

	init(argc, &data, env);
	if (!(ft_strncmp(argv[1], "here_doc", 8)))
		setup_here_doc(&data, argc, argv);
	else
	{
		data.output_file = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data.output_file == -1)
			error("file open error", &data);
		data.input_file = open(argv[1], O_RDONLY);
		if (data.input_file == -1)
			error("file open error", &data);
		dup2(data.input_file, STDIN_FILENO);
		close(data.input_file);
	}
	while (++data.process < (argc - 2))
		child_process(argv[data.process], &data);
	dup2(data.output_file, STDOUT_FILENO);
	close(data.output_file);
	execute(argv[argc - 2], &data);
	return (0);
}
