# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damin <damin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 10:33:57 by damin             #+#    #+#              #
#    Updated: 2024/05/29 10:49:02 by damin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RL_FLAG		= -lreadline -L${HOME}/.brew/opt/readline/lib
NAME		= minishell

SRCS		= minishell.c

OBJS		= $(SRCS:.c=.o)

HAEDERS		= minishell.h
RL_INCLUDES	= -I${HOME}/.brew/opt/readline/include
DEFENDENCY	= $(HAEDERS)

AR			= ar
ARFLAGS		= rcs
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(RL_FLAG) $^ -o $(NAME)

%.o: %.c $(DEFENDENCY)
	$(CC) $(CFLAGS)  -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean bonus fclean re