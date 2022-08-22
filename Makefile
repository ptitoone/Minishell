NAME	= minishell
SRCS	= $(addprefix	srcs/, \
						minishell.c \
						ms_exec_cmd.c \
						ms_init.c \
						ms_substract_quote.c \
						ms_cd.c \
						ms_exec_cmd_pipes.c \
						ms_io_files.c \
						ms_token_format.c \
						ms_echo.c \
						ms_expansion.c \
						ms_lexer.c \
						ms_unset.c \
						ms_envp.c \
						ms_expansion_quote.c \
						ms_print.c \
						ms_envp_btree.c \
						ms_export.c \
						ms_prompt.c \
						ms_envp_parse.c \
						ms_parsing.c \
						ms_free.c \
						ms_signals.c)

OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft.a
LIBS	=   -L. -lft -lcurses -lreadline
INCLS	=   -Iincls

CC		=	gcc
CFLAGS	=	-g -Wall -Werror -Wextra

.PHONY : all clean fclean re

.c.o :
	$(CC) $(CFLAGS) $(INCLS) -c $< -o $@

all : $(LIBFT) $(NAME)

$(LIBFT) :
	make -C libft/ all
	cp libft/$(LIBFT) .
	cp libft/incls/libft.h incls/libft.h

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLS) -o $(NAME) $(LIBS)

clean :
	make -C libft/ clean
	rm -rf incls/libft.h
	rm -rf $(OBJS)


fclean : clean
	make -C libft/ fclean
	rm -rf  $(LIBFT) $(NAME)

re : fclean all
