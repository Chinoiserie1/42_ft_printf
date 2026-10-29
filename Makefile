NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		=	ft_printf.c				\
					handlers.c				\
					check_n_store.c		\
					init.c						\
					add_flags.c				\
					number_utils.c		\
					print_nbr.c				\
					printer.c					\
					ft_putstr.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

# libftprintf.a starts as a copy of libft.a, then gets the printf objects
$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

bonus: all

re: fclean all

FORCE:

.PHONY: all bonus clean fclean re FORCE
