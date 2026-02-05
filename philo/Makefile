NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c read_args.c \
		srcs/ft_atoi.c

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