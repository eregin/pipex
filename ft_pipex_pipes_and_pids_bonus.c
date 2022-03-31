/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pipes_and_pids_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:16:57 by ereginia          #+#    #+#             */
/*   Updated: 2021/12/21 16:30:54 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**ft_piping(int count)
{
	int	i;
	int	**p_pipes;

	i = 0;
	p_pipes = (int **)malloc(sizeof(int *) * (count + 1));
	if (p_pipes == NULL)
		return (NULL);
	while (i < count)
	{
		p_pipes[i] = malloc(sizeof(int) * 2);
		if (p_pipes[i] == NULL || pipe(p_pipes[i]) < 0)
		{
			ft_putstr_fd("pipe creation error\n", 2);
			while (i > 0)
			{
				free(p_pipes[i]);
				i--;
			}
			free(p_pipes);
			return (NULL);
		}
		i++;
	}
	return (p_pipes);
}

int	*ft_piding(int count)
{
	int	i;
	int	*p_pids;

	i = 0;
	p_pids = (int *)malloc(sizeof(int) * count);
	return (p_pids);
}

void	close_unusedpipes(int **pipes, int pipe_num1, int pipe_num2, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if ((i != pipe_num1) && (i != pipe_num2))
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

void	wait_all_pids(int pids_count)
{
	int	i;

	i = 0;
	while (i++ < pids_count)
		wait(NULL);
}

void	args_init(t_args *args, int argc, char **argv, char **envp)
{
	args->argc = argc;
	args->argv = argv;
	args->envp = envp;
}
