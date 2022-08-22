NAME	=	libft.a
INCLS	=	-Iincls
SRCS	=	srcs/ft_affect_to_tab.c \
				srcs/ft_ato.c \
				srcs/ft_bzero.c \
				srcs/ft_calloc.c \
				srcs/ft_check_overflow.c \
				srcs/ft_error.c \
				srcs/ft_free_all.c \
				srcs/ft_freellers_types.c \
				srcs/ft_freellers_types_2_post.c \
				srcs/ft_freellers_types_2_pre.c \
				srcs/ft_isalnum.c \
				srcs/ft_isalpha.c \
				srcs/ft_isascii.c \
				srcs/ft_isdigit.c \
				srcs/ft_isprint.c \
				srcs/ft_issigned.c \
				srcs/ft_isspace.c \
				srcs/ft_toa.c \
				srcs/ft_lstadd_back.c \
				srcs/ft_lstadd_front.c \
				srcs/ft_lstclear.c \
				srcs/ft_lstdelone.c \
				srcs/ft_lstiter.c \
				srcs/ft_lstlast.c \
				srcs/ft_lstmap.c \
				srcs/ft_lstnew.c \
				srcs/ft_lstsize.c \
				srcs/ft_mallocers_types.c \
				srcs/ft_mallocers_types_2.c \
				srcs/ft_manipulate_fd.c \
				srcs/ft_memccpy.c \
				srcs/ft_memchr.c \
				srcs/ft_memcmp.c \
				srcs/ft_memcpy.c \
				srcs/ft_memmove.c \
				srcs/ft_memset.c \
				srcs/ft_printf.c \
				srcs/ft_printf_c.c \
				srcs/ft_printf_check.c \
				srcs/ft_printf_get_conv_type.c \
				srcs/ft_printf_handle_conv.c \
				srcs/ft_printf_has_asterisk.c \
				srcs/ft_printf_has_dot.c \
				srcs/ft_printf_has_flag.c \
				srcs/ft_printf_has_precision.c \
				srcs/ft_printf_has_width.c \
				srcs/ft_printf_i.c \
				srcs/ft_printf_int_len.c \
				srcs/ft_printf_is_spec.c \
				srcs/ft_printf_p.c \
				srcs/ft_printf_pad_space.c \
				srcs/ft_printf_pad_zero.c \
				srcs/ft_printf_parse_conv.c \
				srcs/ft_printf_putchar.c \
				srcs/ft_printf_putnbr.c \
				srcs/ft_printf_putstr_len.c \
				srcs/ft_printf_replace_asterisk.c \
				srcs/ft_printf_s.c \
				srcs/ft_printf_u.c \
				srcs/ft_printf_ux.c \
				srcs/ft_printf_x.c \
				srcs/ft_putchar_fd.c \
				srcs/ft_putendl_fd.c \
				srcs/ft_putnbr_fd.c \
				srcs/ft_putstr_fd.c \
				srcs/ft_realloc.c \
				srcs/ft_split.c \
				srcs/ft_strchr.c \
				srcs/ft_strcmp.c \
				srcs/ft_strdup.c \
				srcs/ft_strjoin.c \
				srcs/ft_strlcat.c \
				srcs/ft_strlcpy.c \
				srcs/ft_strlen.c \
				srcs/ft_strmapi.c \
				srcs/ft_strncmp.c \
				srcs/ft_strnstr.c \
				srcs/ft_strrchr.c \
				srcs/ft_strrev.c \
				srcs/ft_strtrim.c \
				srcs/ft_substr.c \
				srcs/ft_tolower.c \
				srcs/ft_toupper.c \
				srcs/get_next_line.c
OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror 
CC		=	gcc

.PHONY : all clean fclean re

all :	$(NAME)

$(NAME) :	echobjs $(OBJS)
	@$(info - Archiving Libft object files...)
	@ar rcs $(NAME) $(OBJS)

echobjs :
	@$(info - Assembling Libft object files...)

%.o : %.c
	@$(CC) $(CFLAGS) $(INCLS) -c $< -o $@

clean :
	@$(info - Cleaning Libft object files...)
				@rm -rf $(OBJS)

fclean : clean 
	@$(info - Cleaning Libft library file...)
				@rm -rf $(NAME)

re : fclean all
	@$(info - Rebuilding Libft library project...)

