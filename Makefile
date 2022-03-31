# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/12 17:20:51 by ereginia          #+#    #+#              #
#    Updated: 2021/12/22 12:57:30 by ereginia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = pipex

LIBFTNAME = libft.a

CFLAGS = -Werror -Wall -Wextra

OBJS = ${SRCS:.c=.o}

OBJS_B = ${SRCS_B:.c=.o}

SRC = pipex.c ft_pipex_utils.c

SRCS_B = pipex_bonus.c ft_heredoc_bonus.c ft_pipex_multipipes_bonus.c\
		ft_pipex_pipes_and_pids_bonus.c ft_pipex_utils_bonus.c

LIBFTPATH = ./libft/

HEADER = pipex.h

HEADER_B = pipex_bonus.h

all: $(NAME)

${NAME}: ${SRC} ${OBJS} ${HEADER}
	make -C ${LIBFTPATH}
	mv $(LIBFTPATH)${LIBFTNAME} ${LIBFTNAME}
	${CC} ${CFLAGS} ${SRC} ${LIBFTNAME} -o ${NAME}

bonus:	${SRCS_B} ${OBJS_B} ${HEADER_B}
	make -C ${LIBFTPATH}
	mv $(LIBFTPATH)${LIBFTNAME} ${LIBFTNAME}
	${CC} ${CFLAGS} ${SRCS_B} ${LIBFTNAME} -o ${NAME}

clean:
	make clean -C ${LIBFTPATH}
	rm -rf *.o

fclean: clean
	make fclean -C ${LIBFTPATH}
	rm -f $(LIBFTNAME) ${OBJS} ${OBJS_B} $(NAME)

re: fclean ${NAME}
	




