NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
TSAN_FLAGS = -fsanitize=thread -g

SRC = arg_check.c cleanup.c init.c main.c monitor.c routine.c simulation.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

tsan:
	$(CC) $(TSAN_FLAGS) $(SRC) -o tsan_philo -pthread

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) tsan_philo

re: fclean all

.PHONY: all clean fclean re tsan