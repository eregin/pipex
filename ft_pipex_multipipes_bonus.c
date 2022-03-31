/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_multipipes_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:41:44 by ereginia          #+#    #+#             */
/*   Updated: 2021/12/21 16:14:59 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	readfile_process(int *fd, char **argv, char **envp)
{
	int		fd1;
	char	**argVec1;
	char	*file_path;

	ft_dup(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	file_path = ft_open(envp, argv[1], 1);
	fd1 = open(file_path, O_RDONLY);
	free(file_path);
	if (fd1 == -1)
	{
		ft_putstr_fd("can't open infile\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_dup(fd1, 0);
	argVec1 = ft_split(argv[2], ' ');
	execve(ft_exist(envp, argVec1[0]), argVec1, envp);
}

void	writeinfile_process(int argc, int *fd, char **argv, char **envp)
{
	int		fd2;
	char	**argVec2;
	char	*file_path;

	file_path = ft_open(envp, argv[argc - 1], 0);
	fd2 = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	free(file_path);
	if (fd2 == -1)
	{
		ft_putstr_fd("can't create outfile\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_dup(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	ft_dup(fd2, 1);
	argVec2 = ft_split(argv[argc - 2], ' ');
	execve(ft_exist(envp, argVec2[0]), argVec2, envp);
}

void	meanwhile(int *pipe1, int *pipe2, int i, t_args args)
{
	char	**argVec;

	close(pipe1[1]);
	ft_dup(pipe1[0], 0);
	close(pipe1[0]);
	close(pipe2[0]);
	ft_dup(pipe2[1], 1);
	close(pipe2[1]);
	argVec = ft_split(args.argv[i], ' ');
	execve(ft_exist(args.envp, argVec[0]), argVec, args.envp);
}

void	ft_comand_loop(t_args args, int *pids, int **pipes)
{
	int	i;

	i = 1;
	while (i < args.argc - 4)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			close_unusedpipes(pipes, (i - 1), i, (args.argc - 2));
			meanwhile(pipes[i - 1], pipes[i], (i + 2), args);
		}
		i++;
	}
}
