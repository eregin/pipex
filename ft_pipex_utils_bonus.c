/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:48:33 by ereginia          #+#    #+#             */
/*   Updated: 2021/12/21 16:14:03 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_exist(char **envp, char *cmd)
{
	char	**path;
	char	*buf;
	char	*buf2;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) && envp[i] != NULL)
		i++;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i] != NULL)
	{
		buf = ft_strjoin(path[i], "/");
		buf2 = ft_strjoin(buf, cmd);
		free(buf);
		if (!access(buf2, 0))
		{
			free(path);
			return (buf2);
		}
		free(buf2);
		i++;
	}
	free(path);
	return (NULL);
}

char	*ft_open(char **envp, char *filename, int filecheck)
{
	char	*path;
	char	*buf;
	char	*buf2;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PWD", 3) && envp[i] != NULL)
		i++;
	path = envp[i] + 4;
	i = 0;
	buf = ft_strjoin(path, "/");
	buf2 = ft_strjoin(buf, filename);
	free(buf);
	if (!access(buf2, 0) || !filecheck)
		return (buf2);
	free(buf2);
	return (NULL);
}

int	ft_dup(int old, int newfd)
{
	int	buf;

	buf = dup2(old, newfd);
	if (buf == -1)
	{
		ft_putstr_fd("dup2 error\n", 2);
		exit(EXIT_FAILURE);
	}
	return (buf);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_free_pipes_pids(int pipe_count, int **pipes, int *pids)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(pids);
}
