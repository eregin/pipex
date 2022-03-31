/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:29:29 by ereginia          #+#    #+#             */
/*   Updated: 2021/12/21 16:15:26 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	read_heredoc_process(t_args arg, int pipe1[2])
{
	int		readed;
	char	buf[10];

	readed = 1;
	while (readed)
	{
		readed = read(0, &buf, 10);
		if (!ft_strncmp(buf, arg.argv[2], ft_strlen(arg.argv[2])))
			exit(EXIT_SUCCESS);
		write(pipe1[1], &buf, readed);
	}
}

void	medlle_heredoc_process(t_args arg, int *pipe1, int *pipe2)
{
	char	**argVec;

	close(pipe1[1]);
	ft_dup(pipe1[0], 0);
	close(pipe1[0]);
	close(pipe2[0]);
	ft_dup(pipe2[1], 1);
	close(pipe2[1]);
	argVec = ft_split(arg.argv[3], ' ');
	execve(ft_exist(arg.envp, argVec[0]), argVec, arg.envp);
}

void	write_from_heredoc_process(t_args arg, int pipe2[2])
{
	int		fd;
	char	**argVec;
	char	*file_path;

	file_path = ft_open(arg.envp, arg.argv[5], 0);
	fd = open(file_path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	free(file_path);
	if (fd == -1)
	{
		ft_putstr_fd("can't create outfile\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_dup(pipe2[0], 0);
	close(pipe2[0]);
	close(pipe2[1]);
	ft_dup(fd, 1);
	argVec = ft_split(arg.argv[4], ' ');
	execve(ft_exist(arg.envp, argVec[0]), argVec, arg.envp);
}
