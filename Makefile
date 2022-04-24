# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 20:19:03 by jrasser           #+#    #+#              #
#    Updated: 2022/04/08 20:26:19 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= srcs/ft_check_arg.c
				
OBJS			= ${SRCS:.c=.o}
NAME			= pipex
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror
CPPFLAGS		= -I./includes/

${NAME}:		${OBJS}
				gcc -o ${NAME} ${OBJS} main.c -g -L includes/

all:			${NAME}
	
clean:			
				${RM} ${OBJS}
	
fclean:			clean
				${RM} ${NAME}
	
re:				fclean all
	
.PHONY:			all clean fclean re bonus
