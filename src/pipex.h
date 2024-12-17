/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:38:14 by lorey             #+#    #+#             */
/*   Updated: 2024/11/27 16:40:39 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data
{
	char	*path;
	char	**path_split;
	char	*path_with_com;
	char	**path_with_com_split;
	char	**cmd_split;
	int		nbr_malloc;
	int		input_file;
	int		output_file;
	int		process;
	char	*line;
	int		fd[2];
	pid_t	here_pid;
}				t_path_data;

char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	setup_path(char **env, t_path_data *data);
void	error(char *message, t_path_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_next_line(char **line);
void	setup_here_doc(t_path_data *data, int argc, char **argv);
void	here_doc(char *limiter, t_path_data *data);
void	free_double_point(char **pointer);

#endif
