# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efret <efret@student.19.be>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 11:38:36 by efret             #+#    #+#              #
#    Updated: 2024/08/01 09:26:10 by pclaus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS += -fPIC

INCPATH = incl/

SRCPATH = src/
SRCFILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
	   ft_strlen.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
	   ft_strncmp.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c\
	   ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c\
	   ft_memcmp.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	   ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
	   ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c\
	   ft_lstiter.c ft_lstmap.c ft_isspace.c ft_pow.c ft_utoa.c\
	   ft_valid_base.c ft_atoi_base.c ft_itoa_base.c ft_utoa_base.c\
	   ft_convert_base.c ft_ptoa_base.c\
	   ft_printf.c ft_printf_utils.c get_next_line.c\
	   ft_putstr_color.c

SRCS = $(addprefix ${SRCPATH}, ${SRCFILES})

OBJPATH = obj/
OBJFILES = ${SRCFILES:.c=.o}
OBJS = $(addprefix ${OBJPATH}, ${OBJFILES})

#############################################
###					COLORS			      ###
#############################################

RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
CYAN			= \033[0;36m
DEFAULT 		= \e[0m
UP 				= \e[F
CLEAR_LINE 		= \e[2K\r

TOTAL := $(words ${SRCFILES})
COUNT = $(eval HIT_N != expr ${HIT_N} + 1)${HIT_N}
PROG = echo -n "${YELLOW}[`expr ${COUNT} '*' 100 '/' ${TOTAL}`%] ${DEFAULT}"

all: ${NAME}

${NAME}: ${OBJS}
	@echo -n "${YELLOW}"
	@ar rcs ${NAME} ${OBJS}
	@echo "${GREEN}${NAME} Done compiling${DEFAULT}"

${OBJPATH}%.o: ${SRCPATH}%.c ${INCPATH} | ${OBJPATH}
	@${PROG}
	@echo -n "${YELLOW}$(basename $(notdir $<))${DEFAULT}"
	@${CC} ${CFLAGS} -I ${INCPATH} -c -o $@ $<
	@echo -n "${CLEAR_LINE}"

${OBJPATH}:
	@mkdir $@

clean:
	@rm -rf ${OBJPATH}

fclean: clean
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
