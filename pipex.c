/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:52:26 by ereginia          #+#    #+#             */
/*   Updated: 2021/12/21 16:12:35 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	fd2 = open(file_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
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

int	main(int argc, char **argv, char **envp)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("pipex should be: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	if (pipe(fd) == -1)
		return (2);
	pid1 = ft_fork();
	if (pid1 == 0)
		readfile_process(fd, argv, envp);
	pid2 = ft_fork();
	if (pid2 == 0)
		writeinfile_process(argc, fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
