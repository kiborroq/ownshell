# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 11:14:47 by kiborroq          #+#    #+#              #
#    Updated: 2020/11/02 16:57:10 by kiborroq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

FT			= ft

LIBFT_DIR 	= libft/
SRCS_DIR	= srcs/
INCL_DIR	= incs/

SRCS		= ${SRCS_DIR}main.c \
			${SRCS_DIR}comand_parsing_1.c \
			${SRCS_DIR}comand_parsing_2.c \
			${SRCS_DIR}parsing_get_content.c \
			${SRCS_DIR}parsing_utils.c \
			${SRCS_DIR}do_with_strs.c \
			${SRCS_DIR}error_message_treat.c \
			${SRCS_DIR}utils.c 

OBJS		= ${SRCS:.c=.o}

CC			= gcc
CFLAGS		= -Werror -Wextra -Wall -g

LIBS		= -L ${LIBFT_DIR} -l${FT}

.c.o :
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCL_DIR}

${NAME} : 	${OBJS}
			@make bonus -C ${LIBFT_DIR}
			@echo Create ${NAME}
			@${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}

all :		${NAME}

clean :
			@make clean -C ${LIBFT_DIR}
			@rm -f ${OBJS}

fclean : 	clean
			@make fclean -C ${LIBFT_DIR}
			@echo Remove ${NAME}
			@rm -f ${NAME}

re : 		fclean all

.PHONY: 	all clean fclean re .c.o test
