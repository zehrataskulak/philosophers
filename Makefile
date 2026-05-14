NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c read_args.c init_srcs.c print_action.c philos_function.c philos_function_helper.c \
		srcs/z_atoi.c srcs/ft_strchr.c srcs/z_usleep.c srcs/ft_strcmp.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)	

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re