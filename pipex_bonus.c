/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:10:50 by ereginia          #+#    #+#             */
/*   Updated: 2021/12/22 12:56:15 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	multipipes_forking(t_args arg, int **pipes, int *pids)
{
	pids[0] = fork();
	if (pids[0] == 0)
	{
		close_unusedpipes(pipes, 0, -1, (arg.argc - 2));
		readfile_process(pipes[0], arg.argv, arg.envp);
	}
	if (arg.argc > 5)
		ft_comand_loop(arg, pids, pipes);
	pids[arg.argc - 4] = fork();
	if (pids[arg.argc - 4] == 0)
	{
		close_unusedpipes(pipes, (arg.argc - 5), -1, (arg.argc - 2));
		writeinfile_process(arg.argc, pipes[arg.argc - 5], arg.argv, arg.envp);
	}
}

void	multiplepipes(t_args arg)
{
	int		**pipes;
	int		*pids;

	pipes = ft_piping(arg.argc - 2);
	pids = ft_piding(arg.argc - 1);
	multipipes_forking(arg, pipes, pids);
	close_unusedpipes(pipes, -1, -1, (arg.argc - 2));
	wait_all_pids(arg.argc - 2);
	ft_free_pipes_pids(arg.argc - 2, pipes, pids);
}

void	heredoc_forking(t_args arg, int **pipes, int *pids)
{
	pids[0] = ft_fork();
	if (pids[0] == 0)
	{
		close_unusedpipes(pipes, 0, -1, 2);
		read_heredoc_process(arg, pipes[0]);
	}
	pids[1] = ft_fork();
	if (pids[1] == 0)
	{
		close_unusedpipes(pipes, 0, 1, 2);
		medlle_heredoc_process(arg, pipes[0], pipes[1]);
	}
	pids[2] = ft_fork();
	if (pids[2] == 0)
	{
		close_unusedpipes(pipes, -1, 1, 2);
		write_from_heredoc_process(arg, pipes[1]);
	}
}

void	heredoc(t_args arg)
{
	int		**pipes;
	int		*pids;

	pipes = ft_piping(2);
	pids = ft_piding(3);
	heredoc_forking(arg, pipes, pids);
	close_unusedpipes(pipes, -1, -1, 2);
	wait_all_pids(3);
	ft_free_pipes_pids(2, pipes, pids);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	arg;

	args_init(&arg, argc, argv, envp);
	if (argc < 5)
	{
		ft_putstr_fd("pipex should be:", 2);
		ft_putstr_fd(" ./pipex file1 cmd[1] ... cmd[n] file2\n", 2);
		ft_putstr_fd("or: ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		return (1);
	}
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
	{
		if (argc == 6)
			heredoc(arg);
		else
		{
			ft_putstr_fd("pipex should be:", 2);
			ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n", 2);
			return (1);
		}	
	}
	else
		multiplepipes(arg);
	return (1);
}
