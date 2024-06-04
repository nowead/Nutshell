NAME = minishell

CC = cc
# CFLAGS = -fsanitize=address -g #-Wall -Wextra -Werror

HEADER_FLAGS = -Iincludes
LIBFT_FLAGS  = -Llibft -lft
RL_FLAG		 = -lreadline -L${HOME}/.brew/opt/readline/lib
RL_INCLUDES	 = -I${HOME}/.brew/opt/readline/include

LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_HEADER	=	$(addprefix $(LIBFT_DIR), libft.h ft_printf.h get_next_line.h)
HEADER			=	$(addprefix $(HEADER_DIR), $(HEADER_FILES))
SRC				=	sources/parser_main.c \
					$(addprefix $(LEXER_DIR), $(LEXER_SRC)) \
					$(addprefix $(PARSER_DIR), $(PARSER_SRC))\
					$(addprefix $(PROMPT_DIR), $(PROMPT_SRC))
OBJ				=	$(patsubst %.c, %.o, $(SRC))

LIBFT_DIR = libft/
HEADER_DIR = includes/
LEXER_DIR = sources/lexer/
PARSER_DIR = sources/parser/
PROMPT_DIR = sources/prompt/

HEADER_FILES	=	minishell.h tokenize.h	parse.h prompt.h
LEXER_SRC		=	tokenize.c	tokenlist.c	tokenize_handle_token.c	tokenize_classify_operator.c
PARSER_SRC		=	parse.c		parsetree.c	is_assignment_word.c	print_ast.c
PROMPT_SRC		=	prompt.c
LIBFT_SRC = $(addprefix $(LIBFT_DIR), \
ft_isalpha.c    ft_memchr.c     ft_putchar_fd.c ft_strchr.c     ft_strlcpy.c    ft_strrchr.c	ft_atoi.c\
ft_atol.c		ft_isascii.c    ft_isspace.c	ft_memcmp.c     ft_putendl_fd.c ft_strdup.c     ft_strlen.c\
ft_strtrim.c	ft_bzero.c      ft_isdigit.c    ft_memcpy.c     ft_putnbr_fd.c  ft_striteri.c   ft_strmapi.c\
ft_substr.c		ft_calloc.c     ft_isprint.c    ft_memmove.c    ft_putstr_fd.c  ft_strjoin.c    ft_strncmp.c\
ft_tolower.c	ft_isalnum.c    ft_itoa.c       ft_memset.c     ft_split.c      ft_strlcat.c    ft_strnstr.c\
ft_toupper.c	ft_strlncpy.c	ft_strlncat.c	ft_strtol.c\
ft_printf.c						ft_printf_make_str_cs.c			ft_printf_make_str_pdux.c\
ft_printf_make_str_spec1.c		ft_printf_make_str_spec2.c		ft_printf_print_format_string.c\
ft_printf_read_spec.c\
ft_dprintf.c	ft_vdprintf.c	ft_snprintf.c	ft_vsnprintf.c\
get_next_line.c					get_next_line_utils.c)
LIBFT_OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(RL_FLAG) $(LIBFT_FLAGS) -o $@
	@echo "\033[0;33mminshell\033[0m compiled."

$(LIBFT): $(LIBFT_SRC) $(LIBFT_HEADER)
	@make -C $(LIBFT_DIR)
	@echo "\033[0;32mlibft\033[0m compiled."

sources/%.o: sources/%.c $(HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) -Ilibft -Iincludes -c $< -o $@

sources/lexer/%.o: sources/lexer/%.c $(HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) -Ilibft -Iincludes -c $< -o $@

sources/parser/%.o: sources/parser/%.c $(HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) -Ilibft -Iincludes -c $< -o $@

sources/prompt/%.o: sources/prompt/%.c $(HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) $(RL_FLAG) -Ilibft -Iincludes -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[0;32mobjects\033[0m removed."
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[0;32mlibft\033[0m removed."

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31mminishell\033[0m removed."

re: fclean all

.PHONY: all clean fclean re
# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: damin <damin@student.42.fr>                +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2024/05/29 10:33:57 by damin             #+#    #+#              #
# #    Updated: 2024/05/29 14:37:54 by damin            ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

# CC			= cc
# CFLAGS		= -Wall -Wextra -Werror
# RL_FLAG		= -lreadline -L${HOME}/.brew/opt/readline/lib
# NAME		= minishell

# SRCS		= minishell.c

# OBJS		= $(SRCS:.c=.o)

# HAEDERS		= minishell.h
# RL_INCLUDES	= -I${HOME}/.brew/opt/readline/include
# DEFENDENCY	= $(HAEDERS)

# AR			= ar
# ARFLAGS		= rcs
# RM			= rm -f

# all: $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(RL_FLAG) $^ -o $(NAME)

# %.o: %.c $(DEFENDENCY)
# 	$(CC) $(CFLAGS)  -c $<

# clean:
# 	$(RM) $(OBJS)

# fclean: clean
# 	$(RM) $(NAME)

# re:
# 	make fclean
# 	make all

# .PHONY: all clean bonus fclean re
