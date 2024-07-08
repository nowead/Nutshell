NAME = minishell

CC = cc
CFLAGS = -g #-Wall -Wextra -Werror

HEADER_FLAGS	=	-Iincludes
LIBFT_FLAGS		=	-Lsources/libft -lft
RL_FLAG			=	-lreadline -L${HOME}/.brew/opt/readline/lib
RL_INCLUDES		=	-I${HOME}/.brew/opt/readline/include
# RL_FLAG		=	-lreadline -L/opt/homebrew/opt/readline/lib
# RL_INCLUDES	=	-I/opt/homebrew/opt/readline/include

LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_HEADER	=	$(addprefix $(LIBFT_DIR), libft.h ft_printf.h get_next_line.h)
HEADER			=	$(addprefix $(HEADER_DIR), $(HEADER_FILES))
SRC				=	sources/main.c\
					$(addprefix $(INTERFACE_DIR), $(INTERFACE_SRC))\
					$(addprefix $(TOKENIZER_DIR), $(TOKENIZER_SRC)) \
					$(addprefix $(PARSER_DIR), $(PARSER_SRC))\
					$(addprefix $(EXECUTOR_DIR), $(EXECUTOR_SRC))\
					$(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC))\
					$(addprefix $(UTILITIES_DIR), $(UTILITIES_SRC))
OBJ				=	$(patsubst %.c, %.o, $(SRC))

LIBFT_DIR		=	sources/libft/
HEADER_DIR		=	includes/
INTERFACE_DIR	=	sources/interface/
TOKENIZER_DIR	=	sources/tokenizer/
PARSER_DIR		=	sources/parser/
EXECUTOR_DIR	=	sources/executor/
BUILTINS_DIR	=	sources/builtins/
UTILITIES_DIR	=	sources/utilities/

HEADER_FILES	=	minishell.h	interface.h	tokenizer.h	parser.h	executor.h	builtins.h	utilities.h
TOKENIZER_SRC	=	tokenize.c				token_creation_handler.c			operator_token_creation_handler.c\
					operator_token_classification.c		token_creation.c		token_addition.c\
					token_free.c	token_removal.c
PARSER_SRC		=	parse.c		parsetree.c	is_assignment_word.c	split_into_subtokens.c\
					expand_subtokenlist.c	expand_parameter.c		get_token_type_string.c
INTERFACE_SRC	=	interface.c	signal.c
EXECUTOR_SRC	=	execute_ast.c			io.c		ft_execvpe.c	ft_getenv.c
BUILTINS_SRC	=	handle_built_in.c		cd.c		echo.c			env.c		exit.c\
					export.c		pwd.c	unset.c
UTILITIES_SRC	=	err_exit.c				err_return.c			ft_free_strs.c	ft_print_strs.c\
					ft_strcmp.c				ft_strslen.c

LIBFT_SRC		=	$(addprefix $(LIBFT_DIR), \
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
	@$(CC) $(CFLAGS) $(RL_INCLUDES) -Isources/libft -Iincludes -c $< -o $@

sources/tokenizer/%.o: sources/tokenizer/%.c $(HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) -Isources/libft -Iincludes -c $< -o $@

sources/parser/%.o: sources/parser/%.c $(HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) -Isources/libft -Iincludes -c $< -o $@

sources/interface/%.o: sources/interface/%.c $(HEADER) $(LIBFT_HEADER)
	@$(CC) $(CFLAGS) $(RL_INCLUDES) -Isources/libft -Iincludes -c $< -o $@

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
