NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

HEADER = libft.h
PRINTF_HEADER = ft_printf.h
GNL_HEADER = get_next_line.h

SRCS =\
ft_isalpha.c    ft_memchr.c     ft_putchar_fd.c ft_strchr.c     ft_strlcpy.c    ft_strrchr.c	ft_atoi.c\
ft_atol.c		ft_isascii.c    ft_isspace.c	ft_memcmp.c     ft_putendl_fd.c ft_strdup.c     ft_strlen.c\
ft_strtrim.c	ft_bzero.c      ft_isdigit.c    ft_memcpy.c     ft_putnbr_fd.c  ft_striteri.c   ft_strmapi.c\
ft_substr.c		ft_calloc.c     ft_isprint.c    ft_memmove.c    ft_putstr_fd.c  ft_strjoin.c    ft_strncmp.c\
ft_tolower.c	ft_isalnum.c    ft_itoa.c       ft_memset.c     ft_split.c      ft_strlcat.c    ft_strnstr.c\
ft_toupper.c	ft_strlncpy.c	ft_strlncat.c\
ft_printf.c						ft_printf_make_str_cs.c			ft_printf_make_str_pdux.c\
ft_printf_make_str_spec1.c		ft_printf_make_str_spec2.c		ft_printf_print_format_string.c\
ft_printf_read_spec.c\
ft_dprintf.c	ft_vdprintf.c	ft_snprintf.c	ft_vsnprintf.c\
get_next_line.c					get_next_line_utils.c
OBJS = $(patsubst %.c, %.o, $(SRCS))


all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $^
	ranlib $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

ft_%printf%.o: ft_%printf%.c $(PRINTF_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

get_next_line%.o: get_next_line%.c $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

error_functions%.o: error_functions%.c $(ERROR_FUNCTIONS_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
