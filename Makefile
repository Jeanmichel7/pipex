# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 20:19:03 by jrasser           #+#    #+#              #
#    Updated: 2022/04/29 19:56:40 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= srcs/ft_check.c srcs/ft_split.c srcs/ft_strlen.c \
				srcs/ft_strjoin.c srcs/ft_strncmp.c \
				srcs/ft_strtrim.c

OBJS			= ${SRCS:.c=.o}
NAME			= pipex
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
CPPFLAGS		= -I./includes/

${NAME}:		${OBJS}
				gcc -o ${NAME} ${OBJS} main.c -L includes/

all:			${NAME}

clean:			
				${RM} ${OBJS}

fclean:			clean
				${RM} ${NAME}
	
re:				fclean all

.PHONY:			all clean fclean re bonus
