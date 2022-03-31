/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:49:30 by ereginia          #+#    #+#             */
/*   Updated: 2021/12/21 16:14:20 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_args;

int		ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_exist(char **envp, char *cmd);
char	*ft_open(char **envp, char *filename, int filecheck);
int		ft_dup(int old, int newfd);
int		ft_fork(void);
int		**ft_piping(int count);
int		*ft_piding(int count);
void	readfile_process(int *fd, char **argv, char **envp);
void	writeinfile_process(int argc, int *fd, char **argv, char **envp);
void	meanwhile(int *pipe1, int *pipe2, int i, t_args args);
void	ft_comand_loop(t_args args, int *pids, int **pipes);
void	close_unusedpipes(int **pipes, int pipe_num1, int pipe_num2, int count);
void	wait_all_pids(int pids_count);
void	args_init(t_args *args, int argc, char **argv, char **envp);
void	read_heredoc_process(t_args arg, int pipe1[2]);
void	write_from_heredoc_process(t_args arg, int pipe2[2]);
void	medlle_heredoc_process(t_args arg, int *pipe1, int *pipe2);
void	ft_free_pipes_pids(int pipe_count, int **pipes, int *pids);

#endif
